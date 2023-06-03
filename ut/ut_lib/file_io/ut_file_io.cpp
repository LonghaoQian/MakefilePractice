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
#include "csv_proc.h"
#include <algorithm>

class ut_file_io : public testing::Test
{
   protected:
    virtual void SetUp() { std::cout << "setup file_io testing.... \n"; }
    virtual void TearDown() { std::cout << "teardown file_io testing... \n"; }
};

TEST_F(ut_file_io, csv_read_test_normal)
{
    FileIO::CsvContent<std::string> reference{{"title 1", "1", "c", "po"},
                                  {"title 2", "2", "2", "pcd"},
                                  {"title 3", "3", "d", "1dsfdo"}};
    auto res = FileIO::GetFromCsv("./ut/data/csv_test/data1.csv");
    ASSERT_NE(res.size(), 0u);
    EXPECT_TRUE(reference == res);
}

TEST_F(ut_file_io, csv_read_test_no_file)
{
    auto res = FileIO::GetFromCsv("data.csv");
    EXPECT_EQ(res.size(), 0u);
}

TEST_F(ut_file_io, csv_read_test_nullptr)
{
    auto res = FileIO::GetFromCsv(nullptr);
    EXPECT_EQ(res.size(), 0u);
}

TEST_F(ut_file_io, csv_write_test_nullptr)
{
    FileIO::CsvContent<std::string> reference{{"title 1", "1", "c", "po"},
                                  {"title 2", "2", "2", "pcd"},
                                  {"title 3", "3", "d", "1dsfdo"}};
    auto flag = FileIO::WriteToCsv(nullptr,
                                    reference,
                                    std::ios::trunc);
    EXPECT_FALSE(flag);
}

// test write to csv in overwrite mode
TEST_F(ut_file_io, csv_write_test_normal_trunc)
{
    FileIO::CsvContent<std::string> reference{{"title 1", "1", "c", "po"},
                                  {"title 2", "2", "2", "pcd"},
                                  {"title 3", "3", "d", "1dsfdo"}};
    auto flag = FileIO::WriteToCsv("./ut/data/csv_test/data2.csv",
                                    reference,
                                    std::ios::trunc);
    EXPECT_TRUE(flag);
    auto res = FileIO::GetFromCsv("./ut/data/csv_test/data2.csv");
    ASSERT_NE(res.size(), 0u);
    // compare the contents
    EXPECT_TRUE(reference == res);
    if (reference == res) {
        return;
    }
    std::cout<<"reference:\n";
    // if not equal, show the differenece
    for (auto it = reference.begin(); it != reference.end(); it++) {
        copy((*it).begin(), (*it).end(), std::ostream_iterator<std::string>(std::cout, ","));
        std::cout<<std::endl;
    }
    std::cout<<"res:\n";
    for (auto it = res.begin(); it != res.end(); it++) {
        copy((*it).begin(), (*it).end(), std::ostream_iterator<std::string>(std::cout, ","));
        std::cout<<std::endl;
    }
}

// test write to csv in append mode
TEST_F(ut_file_io, csv_write_test_normal_app)
{
    FileIO::CsvContent<std::string> reference{{"title 1", "1", "c", "po"},
                                  {"title 2", "2", "2", "pcd"},
                                  {"title 3", "3", "d", "1dsfdo"}};
    auto flag = FileIO::WriteToCsv("./ut/data/csv_test/data2.csv",
                                    reference,
                                    std::ios::trunc);
    EXPECT_TRUE(flag);
    flag = FileIO::WriteToCsv("./ut/data/csv_test/data2.csv",
                                    reference,
                                    std::ios::app);
    EXPECT_TRUE(flag);
    FileIO::CsvContent<std::string> reference2;
    reference2.reserve(2 * reference.size());
    reference2.insert(reference2.end(), reference.begin(), reference.end());
    reference2.insert(reference2.end(), reference.begin(), reference.end());
    auto res = FileIO::GetFromCsv("./ut/data/csv_test/data2.csv");
    ASSERT_NE(res.size(), 0u);
    // compare the contents
    EXPECT_TRUE(reference2 == res);
    if (reference2 == res) {
        return;
    }
    // if not equal, show the differenece
    for (auto it = reference2.begin(); it != reference2.end(); it++) {
        copy((*it).begin(), (*it).end(), std::ostream_iterator<std::string>(std::cout, ","));
        std::cout<<std::endl;
    }
    std::cout<<"res:\n";
    for (auto it = res.begin(); it != res.end(); it++) {
        copy((*it).begin(), (*it).end(), std::ostream_iterator<std::string>(std::cout, ","));
        std::cout<<std::endl;
    }
}

// test write to csv for input double
TEST_F(ut_file_io, csv_write_test_normal_double)
{
    FileIO::CsvContent<double> reference{{ 1e9, 0.2, 0.03, -4.0 },
                                { 50.0, 0.1236, 0.0, -91.9}};
    auto flag = FileIO::WriteToCsv("./ut/data/csv_test/data3.csv",
                                    reference,
                                    std::ios::trunc);
    EXPECT_TRUE(flag);
    auto res = FileIO::GetFromCsv("./ut/data/csv_test/data3.csv");
    ASSERT_NE(res.size(), 0u);
    auto resDouble = FileIO::ConvertCsv<double>(res.begin(), res.end());
    // compare the contents
    EXPECT_TRUE(reference == resDouble);
    if (reference == resDouble) {
        return;
    }

    // if not equal, show the differenece
    for (auto it = reference.begin(); it != reference.end(); it++) {
        copy((*it).begin(), (*it).end(), std::ostream_iterator<double>(std::cout, ","));
        std::cout<<std::endl;
    }
    std::cout<<"res:\n";
    for (auto it = resDouble.begin(); it != resDouble.end(); it++) {
        copy((*it).begin(), (*it).end(), std::ostream_iterator<double>(std::cout, ","));
        std::cout<<std::endl;
    }
}