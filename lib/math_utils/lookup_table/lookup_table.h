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
#ifndef LOOKUP_TABLE_H
#define LOOKUP_TABLE_H

#include <utility>
#include "math_utils.h"

namespace MathAuxiliary
{
struct Lookup1DData {
    MatrixXd data;  // input table
    VectorXd ref;   // reference for interpolation. the len of ref must equal to
                    // the rows of data
    double target{0.0};
    bool extrapolation{false};  // whether extrapolation is used when the target
                                // is outside of ref
    bool ascending{false};      // whether the ref is in ascending order
};
std::pair<uint32_t, uint32_t> BinarySearchVector(bool ascending, const VectorXd &p,
                                             double target);

VectorXd LinearInterpolation1D(const VectorXd &dataStart,
                               const VectorXd &dataEnd, double refStart,
                               double refEnd, double target);

double LinearInterpolation2D(const MatrixXd &data, const Vector2i &index_1d,
                              const Vector2i &index_2d,
                              const VectorXd &reference_1d,
                              const VectorXd &reference_2d, double target1,
                              double target2);
VectorXd Lookup1D(const Lookup1DData &input);
}  // namespace MathAuxiliary

#endif
