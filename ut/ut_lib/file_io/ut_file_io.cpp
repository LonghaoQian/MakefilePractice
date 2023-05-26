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

#include "gtest/gtest.h"
#include "csv_read.cpp"
#include <algorithm>

class ut_file_io : public testing::Test
{
   protected:
    virtual void SetUp() { std::cout << "setup file_io testing.... \n"; }
    virtual void TearDown() { std::cout << "teardown file_io testing... \n"; }
};

TEST_F(ut_file_io, csv_read_test_normal)
{
    File_IO::CsvContent reference{{"title 1", "1", "c", "po"},
                                  {"title 2", "2", "2", "pcd"},
                                  {"title 3", "3", "d", "1dsfdo"}};
    auto res = File_IO::GetCsvContent("./ut/data/csv_test/data1.csv");
    ASSERT_NE(res.size(), 0u);
    EXPECT_TRUE(reference == res);
}

TEST_F(ut_file_io, csv_read_test_no_file)
{
    auto res = File_IO::GetCsvContent("data.csv");
    EXPECT_EQ(res.size(), 0u);
}

TEST_F(ut_file_io, csv_read_test_nullptr)
{
    auto res = File_IO::GetCsvContent(nullptr);
    EXPECT_EQ(res.size(), 0u);
}