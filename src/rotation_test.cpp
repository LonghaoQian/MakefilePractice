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

#include <iostream>
#include "attitude_kinematics.h"

int main(void)
{
    Matrix3d cross_matrix;
    cross_matrix << 0.0, 0.1, 0.2, 0.2, -0.3, 0.0, 0.1, -0.1, 0.0;
    Vector3d res = MathAuxiliary::Veemap(cross_matrix);
    std::cout << "res[0] :" << res(0, 0) << "\n";
    return 0;
}