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

#ifndef LIE_ALGEBRA_H
#define LIE_ALGEBRA_H

#include "math_utils.h"


namespace MathAuxiliary
{
/* ---- lie algebra ---- */
// the function maps a cross-product matrix back to the vector
Vector3d Veemap(const Matrix3d &cross_matrix);
void Veemap(const Matrix3d &cross_matrix, Vector3d &vector);
// the lie algebra of  a vector, or the cross-product matrix of a vector
Matrix3d Hatmap(const Vector3d &vector);
void Hatmap(const Vector3d &vector, Matrix3d &matrix);
/* ---- rotation matrix ---- */
// output the rotation matrix based on roll, pitch, and yaw angles
// the rotation matrices obtained here are R21, where 1 frame is the base frame,
// 2 is the rotated frame
RotationMatrix RotationMatrixFromRoll(double phi);
void RotationMatrixFromRoll(double phi, RotationMatrix &R21);
RotationMatrix RotationMatrixFromPitch(double theta);
RotationMatrix RotationMatrixFromYaw(double psi);
constexpr uint32_t VECTOR_EXPRESSION_ROWS = 9;
// distribute the columns of a rotation matrix into a 9 by 1 vector
Matrix<double, VECTOR_EXPRESSION_ROWS, 1> ConvertRotationMatrixToVector(const RotationMatrix &R);
// form a rotation matrix with a 9 by 1 vector by columns
RotationMatrix ConvertVectorToRotationMatrix(const Matrix<double, VECTOR_EXPRESSION_ROWS, 1> &v);

/* ---- quaterion ---- */
constexpr uint32_t AUX_MATRIX_ROWS = 3;
constexpr uint32_t AUX_MATRIX_COLS = 4;
// get the Euler angles by a given quaternion
Vector3d GetEulerAngleFromQuaterion(const Quaterion &quaterion);
// given a set of Euler angles, compute the corresponding quaternion
Quaterion GetQuaterionFromRulerAngle(double roll, double pitch, double yaw);
// the L auxiliary matrix of a quaternion
Matrix<double, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> GetLmatrixFromQuaterion(
    const Quaterion &quaterion);
// the R auxiliary matrix of a quaternion
Matrix<double, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> GetRmatrixFromQuaterion(
    const Quaterion &quaterion);
// compute the rotation matrix corresponding to a quaternion
RotationMatrix GetR_IBFromQuaterion(const Quaterion &quaterion);

}  // namespace MathAuxiliary

#endif