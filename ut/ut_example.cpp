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

class ut_test1 : public testing::Test
{
   protected:
    virtual void SetUp() { std::cout << "setup testing.... \n"; }
    virtual void TearDown() { std::cout << "teardown testing... \n"; }
    uint32_t GetRes(uint32_t a, uint32_t b)
    {
        return static_cast<uint32_t>(static_cast<uint64_t>(a) + b);
    }
};

TEST_F(ut_test1, test_1)
{
    EXPECT_EQ(5u, GetRes(2u, 3u));
}