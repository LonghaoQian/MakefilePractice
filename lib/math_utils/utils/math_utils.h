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
namespace MathAuxiliary
{
// const variables
constexpr uint32_t VECTOR_X = 0;
constexpr uint32_t VECTOR_Y = 1;
constexpr uint32_t VECTOR_Z = 2;

constexpr uint32_t EULER_ROLL = 0;
constexpr uint32_t EULER_PITCH = 1;
constexpr uint32_t EULER_YAW = 2;

constexpr uint32_t QUAT_W = 0;
constexpr uint32_t QUAT_X = 1;
constexpr uint32_t QUAT_Y = 2;
constexpr uint32_t QUAT_Z = 3;

using RotationMatrix = Matrix<double, 3, 3>;
using Quaterion = Matrix<double, 4, 1>;

constexpr double DOUBLE_TOLERANCE = 10e-10;

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