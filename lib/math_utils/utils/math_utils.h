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

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <vector>
#include <Eigen/Core>
#include <Eigen/Geometry>

using namespace Eigen;
using std::string;
using std::vector;

using Float64 = _Float64;
using Float32 = _Float32;
using Uint8 = __uint8_t;
using Uint32 = __uint32_t;
using Uint16 = __uint16_t;
using Int8 = __int8_t;
using Int16 = __int16_t;
using Int32 = __int32_t;
namespace MathAuxiliary
{
// const variables
constexpr Uint8 VECTOR_X = 0;
constexpr Uint8 VECTOR_Y = 1;
constexpr Uint8 VECTOR_Z = 2;

constexpr Uint8 EULER_ROLL = 0;
constexpr Uint8 EULER_PITCH = 1;
constexpr Uint8 EULER_YAW = 2;

constexpr Uint8 QUAT_W = 0;
constexpr Uint8 QUAT_X = 1;
constexpr Uint8 QUAT_Y = 2;
constexpr Uint8 QUAT_Z = 3;

using RotationMatrix = Matrix<Float64, 3, 3>;
using Quaterion = Matrix<Float64, 4, 1>;

constexpr Float64 FLOAT64_TOLERANCE = 10e-10;

/*---------- saturation function -----------------*/
void SaturationElementalWise(VectorXd &output, const VectorXd &upper_limit_,
                             const VectorXd &lower_limit_);

void SaturationElementalWise(VectorXd &output, const double &upper_limit_,
                             const double &lower_limit_);

void SaturationElementalWise(double &output, const double &upper_limit_,
                             const double &lower_limit_);

void SaturationVector(VectorXd &output, const double &upper_limit,
                      const double &lower_limit_);
double SaturationElementalWise(const double &input, const double &upper_limit_,
                               const double &lower_limit_);
}  // namespace MathAuxiliary
#endif