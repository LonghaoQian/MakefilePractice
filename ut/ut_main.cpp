// this is the main entrance of the ut main
#include "gtest/gtest.h"

int main(int argc, char ** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}