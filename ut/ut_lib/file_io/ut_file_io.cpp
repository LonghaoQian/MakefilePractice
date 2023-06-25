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
#include "io_proc.h"
#include <algorithm>

class ut_file_io : public testing::Test
{
   protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
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
    EXPECT_EQ(res.size(), 1u);
}

TEST_F(ut_file_io, csv_write_test_nullptr)
{
    FileIO::CsvContent<std::string> reference{{"title 1", "1", "c", "po"},
                                              {"title 2", "2", "2", "pcd"},
                                              {"title 3", "3", "d", "1dsfdo"}};
    auto flag = FileIO::WriteToCsv(nullptr, reference, std::ios::trunc);
    EXPECT_FALSE(flag);
}

// test write to csv in overwrite mode
TEST_F(ut_file_io, csv_write_test_normal_trunc)
{
    FileIO::CsvContent<std::string> reference{{"title 1", "1", "c", "po"},
                                              {"title 2", "2", "2", "pcd"},
                                              {"title 3", "3", "d", "1dsfdo"}};
    auto flag = FileIO::WriteToCsv("./ut/data/csv_test/data2.csv", reference,
                                   std::ios::trunc);
    EXPECT_TRUE(flag);
    auto res = FileIO::GetFromCsv("./ut/data/csv_test/data2.csv");
    ASSERT_NE(res.size(), 0u);
    // compare the contents
    EXPECT_TRUE(reference == res);
    if (reference == res) {
        return;
    }
    std::cout << "reference:\n";
    // if not equal, show the differenece
    for (auto it = reference.begin(); it != reference.end(); it++) {
        copy((*it).begin(), (*it).end(),
             std::ostream_iterator<std::string>(std::cout, ","));
        std::cout << std::endl;
    }
    std::cout << "res:\n";
    for (auto it = res.begin(); it != res.end(); it++) {
        copy((*it).begin(), (*it).end(),
             std::ostream_iterator<std::string>(std::cout, ","));
        std::cout << std::endl;
    }
}

// test write to csv in append mode
TEST_F(ut_file_io, csv_write_test_normal_app)
{
    FileIO::CsvContent<std::string> reference{{"title 1", "1", "c", "po"},
                                              {"title 2", "2", "2", "pcd"},
                                              {"title 3", "3", "d", "1dsfdo"}};
    auto flag = FileIO::WriteToCsv("./ut/data/csv_test/data2.csv", reference,
                                   std::ios::trunc);
    EXPECT_TRUE(flag);
    flag = FileIO::WriteToCsv("./ut/data/csv_test/data2.csv", reference,
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
        copy((*it).begin(), (*it).end(),
             std::ostream_iterator<std::string>(std::cout, ","));
        std::cout << std::endl;
    }
    std::cout << "res:\n";
    for (auto it = res.begin(); it != res.end(); it++) {
        copy((*it).begin(), (*it).end(),
             std::ostream_iterator<std::string>(std::cout, ","));
        std::cout << std::endl;
    }
}

// test write to csv for input double
TEST_F(ut_file_io, csv_write_test_normal_double)
{
    FileIO::CsvContent<double> reference{{1e9, 0.2, 0.03, -4.0},
                                         {50.0, 0.1236, 0.0, -91.9}};
    auto flag = FileIO::WriteToCsv("./ut/data/csv_test/data3.csv", reference,
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
        copy((*it).begin(), (*it).end(),
             std::ostream_iterator<double>(std::cout, ","));
        std::cout << std::endl;
    }
    std::cout << "res:\n";
    for (auto it = resDouble.begin(); it != resDouble.end(); it++) {
        copy((*it).begin(), (*it).end(),
             std::ostream_iterator<double>(std::cout, ","));
        std::cout << std::endl;
    }
}
// test write to binary
TEST_F(ut_file_io, binary_write_test_normal_double)
{
    std::vector<double> buffer{1.2, 3.4, 2.2, -0.11232, 2323232.0};
    {
        FileIO::WriteBinary<double, 10> writeBinary(
            "./ut/data/binary_test/data1.bin", std::ios::trunc);
        ASSERT_TRUE(writeBinary.Write(buffer.data(), buffer.size()));
    }
    // read the binary file
    std::fstream infile;
    infile.open("./ut/data/binary_test/data1.bin",
                std::ios::binary | std::ios::in);
    ASSERT_TRUE(infile.is_open());
    double res[5];
    ASSERT_TRUE(infile.read(reinterpret_cast<char *>(res), 5 * sizeof(double)));
    infile.close();
    for (size_t i = 0; i < buffer.size(); i++) {
        EXPECT_EQ(buffer[i], res[i]);
    }
}
// test write to binary
TEST_F(ut_file_io, binary_write_test_normal_int)
{
    std::vector<int32_t> buffer{1, -2, 0, 45, 1000000};
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary(
            "./ut/data/binary_test/data2.bin", std::ios::trunc);
        ASSERT_TRUE(writeBinary.Write(buffer.data(), buffer.size()));
    }
    // read the binary file
    std::fstream infile;
    infile.open("./ut/data/binary_test/data2.bin",
                std::ios::binary | std::ios::in);
    ASSERT_TRUE(infile.is_open());
    int32_t res[5];
    ASSERT_TRUE(
        infile.read(reinterpret_cast<char *>(res), 5 * sizeof(int32_t)));
    infile.close();
    for (size_t i = 0; i < buffer.size(); i++) {
        EXPECT_EQ(buffer[i], res[i]);
    }
}
// test
TEST_F(ut_file_io, binary_write_to_buffer_test_normal_int)
{
    constexpr size_t DATA_SIZE = 20;
    std::vector<int32_t> buffer(DATA_SIZE, 0);
    for (size_t i = 0; i < buffer.size(); i++) {
        buffer[i] = i;
    }
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary(
            "./ut/data/binary_test/data3.bin", std::ios::trunc);
        std::for_each(buffer.begin(), buffer.end(), [&writeBinary](int32_t a) {
            ASSERT_TRUE(writeBinary.WriteToBuffer(a));
        });
    }
    int32_t res[DATA_SIZE] = {0};
    // read the binary file
    std::fstream infile;
    infile.open("./ut/data/binary_test/data3.bin",
                std::ios::binary | std::ios::in);
    ASSERT_TRUE(infile.is_open());
    ASSERT_TRUE(infile.read(reinterpret_cast<char *>(res),
                            DATA_SIZE * sizeof(int32_t)));
    infile.close();
    for (size_t i = 0; i < buffer.size(); i++) {
        EXPECT_EQ(buffer[i], res[i]);
    }
}

TEST_F(ut_file_io, binary_write_to_buffer_test_int_need_flush_buffer)
{
    constexpr size_t DATA_SIZE = 16;
    std::vector<int32_t> buffer(DATA_SIZE, 0);
    for (size_t i = 0; i < buffer.size(); i++) {
        buffer[i] = i;
    }
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary(
            "./ut/data/binary_test/data3.bin", std::ios::trunc);
        std::for_each(buffer.begin(), buffer.end(), [&writeBinary](int32_t a) {
            ASSERT_TRUE(writeBinary.WriteToBuffer(a));
        });
    }
    int32_t res[DATA_SIZE] = {0};
    // read the binary file
    std::fstream infile;
    infile.open("./ut/data/binary_test/data3.bin",
                std::ios::binary | std::ios::in);
    ASSERT_TRUE(infile.is_open());
    ASSERT_TRUE(infile.read(reinterpret_cast<char *>(res),
                            DATA_SIZE * sizeof(int32_t)));
    infile.close();
    for (size_t i = 0; i < buffer.size(); i++) {
        EXPECT_EQ(buffer[i], res[i]);
    }
}

// test append data to existing file
TEST_F(ut_file_io, binary_write_to_buffer_test_append_int)
{
    constexpr size_t DATA_SIZE = 16;
    std::vector<int32_t> buffer(DATA_SIZE, 0);
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary(
            "./ut/data/binary_test/data4.bin", std::ios::trunc);
        std::for_each(buffer.begin(), buffer.end(), [&writeBinary](int32_t a) {
            ASSERT_TRUE(writeBinary.WriteToBuffer(a));
        });
    }
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary(
            "./ut/data/binary_test/data4.bin", std::ios::app);
        std::for_each(buffer.begin(), buffer.end(), [&writeBinary](int32_t a) {
            ASSERT_TRUE(writeBinary.WriteToBuffer(a));
        });
    }
    int32_t res[DATA_SIZE * 2] = {0};
    // read the binary file
    std::fstream infile;
    infile.open("./ut/data/binary_test/data4.bin",
                std::ios::binary | std::ios::in);
    ASSERT_TRUE(infile.is_open());
    ASSERT_TRUE(infile.read(reinterpret_cast<char *>(res),
                            2 * DATA_SIZE * sizeof(int32_t)));
    infile.close();
    for (size_t i = 0; i < buffer.size(); i++) {
        EXPECT_EQ(buffer[i], res[i]);
    }
    for (size_t i = 0; i < buffer.size(); i++) {
        EXPECT_EQ(buffer[i], res[i + DATA_SIZE]);
    }
}

// test append data to existing file
TEST_F(ut_file_io, binary_write_to_buffer_test_using_open)
{
    constexpr size_t DATA_SIZE = 16;
    std::vector<int32_t> buffer(DATA_SIZE, 0);
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary;
        ASSERT_TRUE(writeBinary.Open("./ut/data/binary_test/data4.bin",
                                     std::ios::trunc));
        std::for_each(buffer.begin(), buffer.end(), [&writeBinary](int32_t a) {
            ASSERT_TRUE(writeBinary.WriteToBuffer(a));
        });
    }
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary;
        ASSERT_TRUE(
            writeBinary.Open("./ut/data/binary_test/data4.bin", std::ios::app));
        std::for_each(buffer.begin(), buffer.end(), [&writeBinary](int32_t a) {
            ASSERT_TRUE(writeBinary.WriteToBuffer(a));
        });
    }
    int32_t res[DATA_SIZE * 2] = {0};
    // read the binary file
    std::fstream infile;
    infile.open("./ut/data/binary_test/data4.bin",
                std::ios::binary | std::ios::in);
    ASSERT_TRUE(infile.is_open());
    ASSERT_TRUE(infile.read(reinterpret_cast<char *>(res),
                            2 * DATA_SIZE * sizeof(int32_t)));
    infile.close();
    for (size_t i = 0; i < buffer.size(); i++) {
        EXPECT_EQ(buffer[i], res[i]);
    }
    for (size_t i = 0; i < buffer.size(); i++) {
        EXPECT_EQ(buffer[i], res[i + DATA_SIZE]);
    }
}

TEST_F(ut_file_io, binary_write_exception_open_with_nullptr)
{
    constexpr size_t DATA_SIZE = 16;
    std::vector<int32_t> buffer(DATA_SIZE, 0);
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary;
        ASSERT_FALSE(writeBinary.Open(nullptr, std::ios::trunc));
    }
}

TEST_F(ut_file_io, binary_write_exception_already_opened)
{
    constexpr size_t DATA_SIZE = 16;
    std::vector<int32_t> buffer(DATA_SIZE, 0);
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary(
            "./ut/data/binary_test/data4.bin", std::ios::trunc);
        ASSERT_FALSE(writeBinary.Open("./ut/data/binary_test/data4.bin",
                                      std::ios::trunc));
    }
}

TEST_F(ut_file_io, binary_write_exception_no_file)
{
    constexpr size_t DATA_SIZE = 16;
    std::vector<int32_t> buffer(DATA_SIZE, 0);
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary(
            "./ut/data/binary_test/data5.bin", std::ios::app);
        writeBinary.Close();
        ASSERT_FALSE(writeBinary.Write(buffer.data(), buffer.size()));
    }
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary;
        ASSERT_FALSE(writeBinary.Write(buffer.data(), buffer.size()));
    }
}

TEST_F(ut_file_io, binary_write_exception_nullptr)
{
    constexpr size_t DATA_SIZE = 16;
    std::vector<int32_t> buffer(DATA_SIZE, 0);
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary(
            "./ut/data/binary_test/data5.bin", std::ios::app);
        ASSERT_FALSE(writeBinary.Write(nullptr, buffer.size()));
    }
}

TEST_F(ut_file_io, binary_write_to_buffer_exception_no_file)
{
    constexpr size_t DATA_SIZE = 16;
    std::vector<int32_t> buffer(DATA_SIZE, 0);
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary(
            "./ut/data/binary_test/data5.bin", std::ios::app);
        writeBinary.Close();
        ASSERT_FALSE(writeBinary.WriteToBuffer(buffer[0]));
    }
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary;
        ASSERT_FALSE(writeBinary.WriteToBuffer(buffer[0]));
    }
}

TEST_F(ut_file_io, binary_flush_buffer_exception_no_file)
{
    constexpr size_t DATA_SIZE = 16;
    std::vector<int32_t> buffer(DATA_SIZE, 0);
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary(
            "./ut/data/binary_test/data5.bin", std::ios::app);
        writeBinary.Close();
        ASSERT_FALSE(writeBinary.FlushBuffer());
    }
    {
        FileIO::WriteBinary<int32_t, 10> writeBinary;
        ASSERT_FALSE(writeBinary.FlushBuffer());
    }
}
