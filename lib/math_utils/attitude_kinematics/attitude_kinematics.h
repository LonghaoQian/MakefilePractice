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

#ifndef LIE_ALGEBRA_H
#define LIE_ALGEBRA_H

#include "math_utils.h"
namespace MathAuxiliary
{
/* ---- lie algebra ---- */
// the function maps a cross-product matrix back to the vector
Vector3d Veemap(const Matrix3d &cross_matrix);
// the lie algebra of  a vector, or the cross-product matrix of a vector
Matrix3d Hatmap(const Vector3d &vector);

/* ---- rotation matrix ---- */
// output the rotation matrix based on roll, pitch, and yaw angles
// the rotation matrices obtained here are R21, where 1 frame is the base frame,
// 2 is the rotated frame
RotationMatrix RotationMatrixFromRoll(Float64 phi);
RotationMatrix RotationMatrixFromPitch(Float64 theta);
RotationMatrix RotationMatrixFromYaw(Float64 psi);
// distribute the columns of a rotation matrix into a 9 by 1 vector
Matrix<Float64, 9, 1> ConvertRotationMatrixToVector(const RotationMatrix &R);
// form a rotation matrix with a 9 by 1 vector by columns
RotationMatrix ConvertVectorToRotationMatrix(const Matrix<Float64, 9, 1> &v);

/* ---- quaterion ---- */
constexpr Uint32 AUX_MATRIX_ROWS = 3;
constexpr Uint32 AUX_MATRIX_COLS = 4;
// get the Euler angles by a given quaternion
Vector3d GetEulerAngleFromQuaterion(const Quaterion &quaterion);
// given a set of Euler angles, compute the corresponding quaternion
Quaterion GetQuaterionFromRulerAngle(Float64 roll, Float64 pitch, Float64 yaw);
// the L auxiliary matrix of a quaternion
Matrix<Float64, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> GetLmatrixFromQuaterion(
    const Quaterion &quaterion);
// the R auxiliary matrix of a quaternion
Matrix<Float64, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> GetRmatrixFromQuaterion(
    const Quaterion &quaterion);
// compute the rotation matrix corresponding to a quaternion
RotationMatrix GetR_IBFromQuaterion(const Quaterion &quaterion);

}  // namespace MathAuxiliary

#endif