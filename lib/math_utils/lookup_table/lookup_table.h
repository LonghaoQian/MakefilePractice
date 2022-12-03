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
    Float32 target{0.0};
    bool extrapolation{false};  // whether extrapolation is used when the target
                                // is outside of ref
    bool ascending{false};      // whether the ref is in ascending order
};
std::pair<Uint32, Uint32> BinarySearchVector(bool ascending, const VectorXd &p,
                                             Float64 target);

VectorXd LinearInterpolation1D(const VectorXd &dataStart,
                               const VectorXd &dataEnd, Float64 refStart,
                               Float64 refEnd, Float64 target);

Float64 LinearInterpolation2D(const MatrixXd &data, const Vector2i &index_1d,
                              const Vector2i &index_2d,
                              const VectorXd &reference_1d,
                              const VectorXd &reference_2d, Float64 target1,
                              Float64 target2);
VectorXd Lookup1D(const Lookup1DData &input);
}  // namespace MathAuxiliary

#endif
