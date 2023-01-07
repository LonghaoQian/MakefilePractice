/*************************************************************

Copyright(C) 2022 Longhao Qian

This program is free software; you can redistribute it and / or
modify it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program;
if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

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
    if (abs(refStart - refEnd) < FLOAT64_TOLERANCE) {
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