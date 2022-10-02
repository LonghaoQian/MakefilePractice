
#include <iostream>
#include <stdint.h>
#include "gtest/gtest.h"

class ut_test1 : public testing::Test {
protected:
    virtual void SetUp()
    {
        std::cout<<"setup testing.... \n";
    }
    virtual void TearDown()
    {
        std::cout<<"teardown testing... \n";
    }
    uint32_t GetRes(uint32_t a, uint32_t b)
    {
        return static_cast<uint32_t>(static_cast<uint64_t>(a) + b);
    }
};

TEST_F(ut_test1, test_1)
{
    EXPECT_EQ(5u, GetRes(2u, 3u));
}