/*************************************************************

MIT License

Copyright (c) 2023 Dr. Longhao Qian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*************************************************************/

#include "lookup_table.h"
namespace MathAuxiliary
{
std::pair<uint32_t, uint32_t> BinarySearchVector(bool ascending, const VectorXd &p,
                                             double target)
{
    if (p.size() <= 1) {
        return {0, 0};
    }
    // Corner cases
    if (ascending) {
        if (target <= p(0)) {
            return {0, 0};
        }
        if (target >= p(p.size() - 1)) {
            return {p.size() - 1, p.size() - 1};
        }
    } else {
        if (target >= p(0)) {
            return {0, 0};
        }
        if (target <= p(p.size() - 1)) {
            return {p.size() - 1, p.size() - 1};
        }
    }
    uint32_t start = 0;
    uint32_t end = p.size() - 1;
    uint32_t mid = 0;
    while (start < end - 1) {
        mid = (start + end) / 2;
        if (ascending) {
            if (p(mid) <= target) {
                start = mid;
            } else {
                end = mid;
            }
        } else {
            if (p(mid) >= target) {
                start = mid;
            } else {
                end = mid;
            }
        }
    }
    return { start, end };
}

// linear interpolation for vector objects
VectorXd LinearInterpolation1D(const VectorXd &dataStart,
                               const VectorXd &dataEnd, double refStart,
                               double refEnd, double target)
{
    if (abs(refStart - refEnd) < DOUBLE_TOLERANCE) {
        // TO DO: add log to complain about this exception
        VectorXd res;
        return res;
    }
    return dataStart +
           (target - refStart) * (dataEnd - dataStart) / (refEnd - refStart);
}

VectorXd Lookup1D(const Lookup1DData &input)
{
    // check the consistency of dimensions
    if (input.data.rows() == 0 || input.data.cols() == 0 ||
        input.ref.size() == 0) {
        // TO DO: add log to show the exception
        VectorXd res;
        return res;
    }
    if (input.data.rows() != input.ref.size()) {
        // TO DO: add log to show the exception
        VectorXd res;
        return res;
    }
    // get the index
    auto index = BinarySearchVector(input.ascending, input.ref, input.target);
    if (index.first == index.second) {
        VectorXd res(input.data.cols());
        if (input.extrapolation) {
            // TO DO: add extrapolation result
            return res;
        } else {
            res = input.data.row(index.first);
            return res;
        }
    } else {
        return LinearInterpolation1D(
            input.data.row(index.first), input.data.row(index.second),
            input.ref(index.first), input.data(index.second), input.target);
    }
}

}  // namespace MathAuxiliary