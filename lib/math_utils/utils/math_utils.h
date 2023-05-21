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