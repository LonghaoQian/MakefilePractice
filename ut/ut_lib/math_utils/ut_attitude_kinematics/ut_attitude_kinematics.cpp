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
#include <stdint.h>
#include "gtest/gtest.h"
#include "attitude_kinematics.cpp"

class ut_attitude_kinematics : public testing::Test
{
   protected:
    virtual void SetUp()
    {
        std::cout << "setup attitude kinematics testing.... \n";
    }
    virtual void TearDown()
    {
        std::cout << "teardown attitude kinematics testing... \n";
    }
};

TEST_F(ut_attitude_kinematics, test_Veemap)
{
    Eigen::Matrix3d input;
    input << 0.0, -0.3, 0.1, 0.1, 0.0, 3.1, -4.0, -3.8, 0.0;
    auto res = MathAuxiliary::Veemap(input);
    EXPECT_EQ(res(MathAuxiliary::VECTOR_X), -input(1, 2));
}