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

void Veemap(const Matrix3d &cross_matrix, Vector3d &vector)
{
    vector(VECTOR_X) = -cross_matrix(1, 2);
    vector(VECTOR_Y) = cross_matrix(0, 2);
    vector(VECTOR_Z) = -cross_matrix(0, 1);
}

void Hatmap(const Vector3d &vector, Matrix3d &cross_matrix)
{
    /*
    r^x = [0 -r3 r2;
    r3 0 -r1;
    -r2 r1 0]
    */
    cross_matrix(0, 0) = 0.0;
    cross_matrix(0, 1) = -vector(VECTOR_Z);
    cross_matrix(0, 2) = vector(VECTOR_Y);

    cross_matrix(1, 0) = vector(VECTOR_Z);
    cross_matrix(1, 1) = 0.0;
    cross_matrix(1, 2) = -vector(VECTOR_X);

    cross_matrix(2, 0) = -vector(VECTOR_Y);
    cross_matrix(2, 1) = vector(VECTOR_X);
    cross_matrix(2, 2) = 0.0;
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

RotationMatrix RotationMatrixFromRoll(double phi)
{
    /*
    R21 = [1 0 0;
           0 cphi sphi;
           0 -sphi cphi];
    */
    double cphi = cos(phi);
    double sphi = sin(phi);
    RotationMatrix R21;
    R21.setZero();
    R21(0, 0) = 1.0;
    R21(1, 1) = cphi;
    R21(2, 2) = cphi;
    R21(1, 2) = sphi;
    R21(2, 1) = -sphi;
    return R21;
}

void RotationMatrixFromRoll(double phi, RotationMatrix &R21)
{
    /*
    R21 = [1 0 0;
           0 cphi sphi;
           0 -sphi cphi];
    */
    double cphi = cos(phi);
    double sphi = sin(phi);
    R21.setZero();
    R21(0, 0) = 1.0;
    R21(1, 1) = cphi;
    R21(2, 2) = cphi;
    R21(1, 2) = sphi;
    R21(2, 1) = -sphi;
}

RotationMatrix RotationMatrixFromPitch(double theta)
{
    /*
    R21 = [ctheta 0 -stheta;
          0   1   0;
          stheta 0 ctheta]
    */
    double ctheta = cos(theta);
    double stheta = sin(theta);
    RotationMatrix R21;
    R21.setZero();
    R21(0, 0) = ctheta;
    R21(0, 2) = -stheta;
    R21(1, 1) = 1.0;
    R21(2, 0) = stheta;
    R21(2, 2) = ctheta;
    return R21;
}

RotationMatrix RotationMatrixFromYaw(double psi)
{
    /*
    R21 = [cpsi spsi 0;
           -spsi cpsi 0;
           0   0  1]
    */
    double cpsi = cos(psi);
    double spsi = sin(psi);
    RotationMatrix R21;
    R21.setZero();
    R21(0, 0) = cpsi;
    R21(0, 1) = spsi;
    R21(1, 0) = -spsi;
    R21(1, 1) = cpsi;
    R21(2, 2) = 1.0;
    return R21;
}

Matrix<double, 9, 1> ConvertRotationMatrixToVector(
    const Matrix<double, 3, 3> &R)
{
    Matrix<double, 9, 1> v;

    v.block<3, 1>(0, 0) = R.block<3, 1>(0, 0);
    v.block<3, 1>(3, 0) = R.block<3, 1>(0, 1);
    v.block<3, 1>(6, 0) = R.block<3, 1>(0, 2);
    return v;
}

RotationMatrix ConvertVectorToRotationMatrix(const Matrix<double, 9, 1> &v)
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
    double sinr_cosp = +2.0 * (quaterion(QUAT_W) * quaterion(QUAT_X) +
                                quaterion(QUAT_Y) * quaterion(QUAT_Z));
    double cosr_cosp = +1.0 - 2.0 * (quaterion(QUAT_X) * quaterion(QUAT_X) +
                                      quaterion(QUAT_Y) * quaterion(QUAT_Y));
    double roll = atan2(sinr_cosp, cosr_cosp);

    // pitch (y-axis rotation)
    double sinp = +2.0 * (quaterion(QUAT_W) * quaterion(QUAT_Y) -
                           quaterion(QUAT_Z) * quaterion(QUAT_X));
    double pitch;
    if (fabs(sinp) >= 1)
        pitch = copysign(M_PI / 2, sinp);  // use 90 degrees if out of range
    else
        pitch = asin(sinp);

    // yaw (z-axis rotation)
    double siny_cosp = +2.0 * (quaterion(QUAT_W) * quaterion(QUAT_Z) +
                                quaterion(QUAT_X) * quaterion(QUAT_Y));
    double cosy_cosp = +1.0 - 2.0 * (quaterion(QUAT_Y) * quaterion(QUAT_Y) +
                                      quaterion(QUAT_Z) * quaterion(QUAT_Z));
    double yaw = atan2(siny_cosp, cosy_cosp);
    Euler(EULER_ROLL) = roll;
    Euler(EULER_PITCH) = pitch;
    Euler(EULER_YAW) = yaw;
    return Euler;
}

Quaterion GetQuaterionFromRulerAngle(double roll, double pitch, double yaw)
{
    Quaterion Quaterion;
    // Abbreviations for the various angular functions
    double cy = cos(yaw * 0.5);
    double sy = sin(yaw * 0.5);
    double cp = cos(pitch * 0.5);
    double sp = sin(pitch * 0.5);
    double cr = cos(roll * 0.5);
    double sr = sin(roll * 0.5);

    Quaterion(QUAT_W) = cy * cp * cr + sy * sp * sr;
    Quaterion(QUAT_X) = cy * cp * sr - sy * sp * cr;
    Quaterion(QUAT_Y) = sy * cp * sr + cy * sp * cr;
    Quaterion(QUAT_Z) = sy * cp * cr - cy * sp * sr;

    return Quaterion;
}

Matrix<double, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> GetLmatrixFromQuaterion(
    const Quaterion &quaterion)
{
    Matrix<double, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> Lmatrix;
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

Matrix<double, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> GetRmatrixFromQuaterion(
    const Quaterion &quaterion)
{
    Matrix<double, AUX_MATRIX_ROWS, AUX_MATRIX_COLS> Rmatrix;
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