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

#include <math.h>
#define _USE_MATH_DEFINES  // for C++
#include "attitude_kinematics.h"

namespace MathAuxiliary
{
Vector3d Veemap(const Matrix3d &cross_matrix)
{
    Vector3d vector;
    vector(VECTOR_X) = -cross_matrix(1, 2);
    vector(VECTOR_Y) = cross_matrix(0, 2);
    vector(VECTOR_Z) = -cross_matrix(0, 1);
    return vector;
}
Matrix3d Hatmap(const Vector3d &vector)
{
    /*
    r^x = [0 -r3 r2;
    r3 0 -r1;
    -r2 r1 0]
    */
    Matrix3d cross_matrix;
    cross_matrix(0, 0) = 0.0;
    cross_matrix(0, 1) = -vector(VECTOR_Z);
    cross_matrix(0, 2) = vector(VECTOR_Y);

    cross_matrix(1, 0) = vector(VECTOR_Z);
    cross_matrix(1, 1) = 0.0;
    cross_matrix(1, 2) = -vector(VECTOR_X);

    cross_matrix(2, 0) = -vector(VECTOR_Y);
    cross_matrix(2, 1) = vector(VECTOR_X);
    cross_matrix(2, 2) = 0.0;
    return cross_matrix;
}

RotationMatrix RotationMatrixFromRoll(Float64 phi)
{
    /*
    R21 = [1 0 0;
           0 cphi sphi;
           0 -sphi cphi];
    */
    Float64 cphi = cos(phi);
    Float64 sphi = sin(phi);
    RotationMatrix R21;
    R21.setZero();
    R21(0, 0) = 1.0;
    R21(1, 1) = cphi;
    R21(2, 2) = cphi;
    R21(1, 2) = sphi;
    R21(2, 1) = -sphi;
    return R21;
}
RotationMatrix RotationMatrixFromPitch(Float64 theta)
{
    /*
    R21 = [ctheta 0 -stheta;
          0   1   0;
          stheta 0 ctheta]
    */
    Float64 ctheta = cos(theta);
    Float64 stheta = sin(theta);
    RotationMatrix R21;
    R21.setZero();
    R21(0, 0) = ctheta;
    R21(0, 2) = -stheta;
    R21(1, 1) = 1.0;
    R21(2, 0) = stheta;
    R21(2, 2) = ctheta;
    return R21;
}

RotationMatrix RotationMatrixFromYaw(Float64 psi)
{
    /*
    R21 = [cpsi spsi 0;
           -spsi cpsi 0;
           0   0  1]
    */
    Float64 cpsi = cos(psi);
    Float64 spsi = sin(psi);
    RotationMatrix R21;
    R21.setZero();
    R21(0, 0) = cpsi;
    R21(0, 1) = spsi;
    R21(1, 0) = -spsi;
    R21(1, 1) = cpsi;
    R21(2, 2) = 1.0;
    return R21;
}

Matrix<Float64, 9, 1> ConvertRotationMatrixToVector(
    const Matrix<Float64, 3, 3> &R)
{
    Matrix<Float64, 9, 1> v;

    v.block<3, 1>(0, 0) = R.block<3, 1>(0, 0);
    v.block<3, 1>(3, 0) = R.block<3, 1>(0, 1);
    v.block<3, 1>(6, 0) = R.block<3, 1>(0, 2);
    return v;
}

RotationMatrix ConvertVectorToRotationMatrix(const Matrix<Float64, 9, 1> &v)
{
    RotationMatrix R;
    R.block<3, 1>(0, 0) = v.block<3, 1>(0, 0);
    R.block<3, 1>(0, 1) = v.block<3, 1>(3, 0);
    R.block<3, 1>(0, 2) = v.block<3, 1>(6, 0);
    return R;
}

Vector3d GetEulerAngleFromQuaterion(const Quaterion &quaterion)
{
    /* Normal means the following
     * https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles
     */
    // roll (x-axis rotation)
    Vector3d Euler;
    Float64 sinr_cosp = +2.0 * (quaterion(QUAT_W) * quaterion(QUAT_X) +
                                quaterion(QUAT_Y) * quaterion(QUAT_Z));
    Float64 cosr_cosp = +1.0 - 2.0 * (quaterion(QUAT_X) * quaterion(QUAT_X) +
                                      quaterion(QUAT_Y) * quaterion(QUAT_Y));
    Float64 roll = atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    Float64 sinp = +2.0 * (quaterion(QUAT_W) * quaterion(QUAT_Y) -
                           quaterion(QUAT_Z) * quaterion(QUAT_X));
    Float64 pitch;
    if (fabs(sinp) >= 1)
        pitch = copysign(M_PI / 2, sinp);  // use 90 degrees if out of range
    else
        pitch = asin(sinp);

    // yaw (z-axis rotation)
    Float64 siny_cosp = +2.0 * (quaterion(QUAT_W) * quaterion(QUAT_Z) +
                                quaterion(QUAT_X) * quaterion(QUAT_Y));
    Float64 cosy_cosp = +1.0 - 2.0 * (quaterion(QUAT_Y) * quaterion(QUAT_Y) +
                                      quaterion(QUAT_Z) * quaterion(QUAT_Z));
    Float64 yaw = atan2(siny_cosp, cosy_cosp);
    Euler(EULER_ROLL) = roll;
    Euler(EULER_PITCH) = pitch;
    Euler(EULER_YAW) = yaw;
    return Euler;
}

Quaterion GetQuaterionFromRulerAngle(Float64 roll, Float64 pitch, Float64 yaw)
{
    Quaterion Quaterion;
    // Abbreviations for the various angular functions
    Float64 cy = cos(yaw * 0.5);
    Float64 sy = sin(yaw * 0.5);
    Float64 cp = cos(pitch * 0.5);
    Float64 sp = sin(pitch * 0.5);
    Float64 cr = cos(roll * 0.5);
    Float64 sr = sin(roll * 0.5);

    Quaterion(QUAT_W) = cy * cp * cr + sy * sp * sr;
    Quaterion(QUAT_X) = cy * cp * sr - sy * sp * cr;
    Quaterion(QUAT_Y) = sy * cp * sr + cy * sp * cr;
    Quaterion(QUAT_Z) = sy * cp * cr - cy * sp * sr;

    return Quaterion;
}

Matrix<Float64, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> GetLmatrixFromQuaterion(
    const Quaterion &quaterion)
{
    Matrix<Float64, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> Lmatrix;
    // update the auxiliary matrix
    /*
    L = [-q1 q0 q3 -q2;
    -q2 -q3 q0 q1;
    -q3 q2 -q1 q0]
    R = [-q1 q0 -q3 q2;
    -q2 q3 q0 -q1;
    -q3 -q2 q1 q0]
    R_IB = RL^T
    */
    Lmatrix(0, 0) = -quaterion(QUAT_X);
    Lmatrix(1, 0) = -quaterion(QUAT_Y);
    Lmatrix(2, 0) = -quaterion(QUAT_Z);

    Lmatrix(0, 1) = quaterion(QUAT_W);
    Lmatrix(1, 2) = quaterion(QUAT_W);
    Lmatrix(2, 3) = quaterion(QUAT_W);

    Lmatrix(0, 2) = quaterion(QUAT_Z);
    Lmatrix(0, 3) = -quaterion(QUAT_Y);
    Lmatrix(1, 1) = -quaterion(QUAT_Z);
    Lmatrix(1, 3) = quaterion(QUAT_X);
    Lmatrix(2, 1) = quaterion(QUAT_Y);
    Lmatrix(2, 2) = -quaterion(QUAT_X);

    return Lmatrix;
}

Matrix<Float64, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> GetRmatrixFromQuaterion(
    const Quaterion &quaterion)
{
    Matrix<Float64, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> Rmatrix;
    Rmatrix(0, 0) = -quaterion(QUAT_X);
    Rmatrix(1, 0) = -quaterion(QUAT_Y);
    Rmatrix(2, 0) = -quaterion(QUAT_Z);

    Rmatrix(0, 1) = quaterion(QUAT_W);
    Rmatrix(1, 2) = quaterion(QUAT_W);
    Rmatrix(2, 3) = quaterion(QUAT_W);

    Rmatrix(0, 2) = -quaterion(QUAT_Z);
    Rmatrix(0, 3) = quaterion(QUAT_Y);
    Rmatrix(1, 1) = quaterion(QUAT_Z);
    Rmatrix(1, 3) = -quaterion(QUAT_X);
    Rmatrix(2, 1) = -quaterion(QUAT_Y);
    Rmatrix(2, 2) = quaterion(QUAT_X);

    return Rmatrix;
}

RotationMatrix GetR_IBFromQuaterion(const Quaterion &quaterion)
{
    // pose[1].R * pose[1].L.transpose();
    RotationMatrix R_IB = GetRmatrixFromQuaterion(quaterion) *
                          GetLmatrixFromQuaterion(quaterion).transpose();
    return R_IB;
}
}  // namespace MathAuxiliary