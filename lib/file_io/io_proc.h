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
#ifndef IO_PROC_H
#define IO_PROC_H

#include <string>
#include <vector>
#include <array>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
namespace FileIO
{
template <typename T>
using CsvContent = std::vector<std::vector<T>>;
using OpenMode =
    std::ios::ios_base::openmode;  // app for append, trunc for overwrite
inline CsvContent<std::string> GetFromCsv(const char *fileName)
{
    if (fileName == nullptr) {
        std::cout << "ERR: invalid file name " << '\n';
        return {};
    }
    std::vector<std::string> row;
    std::fstream file(fileName, std::ios::in);
    std::string line, word;
    if (!file.is_open()) {
        std::cout << "ERR: Can not open file: " << fileName << '\n';
        return {};
    }
    std::vector<std::vector<std::string>> res;
    while (getline(file, line)) {
        row.clear();
        std::stringstream str(line);
        while (getline(str, word, ',')) {
            row.emplace_back(word);
        }
        res.emplace_back(row);
    }
    return res;
}

template <typename T>
bool WriteToCsv(const char *fileName, const CsvContent<T> &content,
                OpenMode mode)
{
    if (fileName == nullptr) {
        std::cout << "ERR: invalid file name " << '\n';
        return false;
    }
    // if file does not exists, create a new file
    std::fstream file(fileName, mode | std::fstream::out);
    std::stringstream temp;
    for (auto it = content.begin(); it != content.end(); it++) {
        temp.str("");
        copy((*it).begin(), (*it).end(), std::ostream_iterator<T>(temp, ","));
        file << temp.str() << '\n';
    }
    return true;
}

// default is double
template <class T>
inline T ConvertString(const std::string &input)
{
    std::cout << "defualt is used!\n";
    return std::stod(input);
}

template <>
inline double ConvertString<double>(const std::string &input)
{
    return std::stod(input);
}

template <>
inline float ConvertString<float>(const std::string &input)
{
    return std::stof(input);
}

template <>
inline long double ConvertString<long double>(const std::string &input)
{
    return std::stold(input);
}

template <>
inline int ConvertString<int>(const std::string &input)
{
    return std::stoi(input);
}

template <>
inline long int ConvertString<long int>(const std::string &input)
{
    return std::stoll(input);
}

template <>
inline unsigned int ConvertString<unsigned int>(const std::string &input)
{
    return std::stoul(input);
}

template <>
inline unsigned long int ConvertString<unsigned long int>(
    const std::string &input)
{
    return std::stoull(input);
}

using CsvContentItr = CsvContent<std::string>::iterator;
template <typename T>
CsvContent<T> ConvertCsv(CsvContentItr beginItr, CsvContentItr endItr)
{
    CsvContent<T> res;
    res.reserve(static_cast<size_t>(std::distance(beginItr, endItr)));
    std::for_each(beginItr, endItr, [&res](const std::vector<std::string> &a) {
        res.push_back({});
        std::for_each(a.begin(), a.end(), [&res](const std::string &b) {
            res.back().push_back(ConvertString<T>(b));
        });
    });
    return res;
}

// write to binary
template <typename T, size_t bufferSize = 128>
class WriteBinary
{
   public:
    using value_type = T;
    static const size_t type_size = sizeof(value_type);
    // rigit now only supports pod
    static_assert(std::is_pod<value_type>::value,
                  "WriteBinary only supports pod!\n");
    WriteBinary(const char *fileName, OpenMode mode)
        : file{fileName, mode | std::fstream::out | std::ios::binary},
          dataItr{dataBuffer.begin()}
    {
    }
    WriteBinary() : dataItr{dataBuffer.begin()} {}
    ~WriteBinary() { FlushBuffer(); }
    WriteBinary(const WriteBinary &) = delete;
    WriteBinary &operator=(const WriteBinary &) = delete;
    bool Open(const char *fileName, OpenMode mode)
    {
        if (file.is_open()) {
            std::cout << "Err, file already opened!\n";
            return false;
        }
        if (fileName == nullptr) {
            std::cout << "Err, file name is nullptr!\n";
            return false;
        }
        file.open(fileName, mode | std::fstream::out | std::ios::binary);
        return true;
    }
    bool Write(value_type *ptr, size_t num)
    {
        if (ptr == nullptr) {
            std::cout << "Err, null ptr!\n";
            return false;
        }
        if (!file.is_open()) {
            std::cout << "Err, can not open file.\n";
            return false;
        }
        file.write(reinterpret_cast<const char *>(ptr), type_size * num);
        return true;
    }

    bool WriteToBuffer(value_type input)
    {
        if (!file.is_open()) {
            std::cout << "Err, can not open file.\n";
            return false;
        }
        *dataItr = input;
        dataItr++;
        bool flag = true;
        if (dataItr == dataBuffer.end()) {
            // if buffer is full, write all to file
            flag = FlushBuffer();
        }
        return flag;
    }

    // write all remaining data in the buffer to the file
    bool FlushBuffer(void)
    {
        if (!file.is_open()) {
            return false;
        }
        if (dataItr == dataBuffer.begin()) {
            return true;  // empty data array does not raise an error
        }
        file.write(reinterpret_cast<const char *>(dataBuffer.data()),
                   type_size * std::distance(dataBuffer.begin(), dataItr));
        // reset the current idx
        dataItr = dataBuffer.begin();
        return true;
    }
    void Close(void)
    {
        if (!file.is_open()) {
            return;
        }
        file.close();
    }

   private:
    // file
    std::fstream file;
    // buffer
    std::array<value_type, bufferSize> dataBuffer;
    // buffer itr (dependent type)
    typename std::array<value_type, bufferSize>::iterator dataItr;
};

template <typename T>
class ReadBinary
{
   public:
    using value_type = T;
    static const size_t type_size = sizeof(value_type);
    explicit ReadBinary(const char *fileName)
        : file{fileName, std::fstream::in | std::ios::binary}
    {
    }
    ReadBinary() {}
    bool Open(const char *fileName)
    {
        if (file.is_open()) {
            std::cout << "Err, file already opened!\n";
            return false;
        }
        if (fileName == nullptr) {
            std::cout << "Err, file name is nullptr!\n";
            return false;
        }
        // close the current file
        Close();
        // then open a new file
        file.open(fileName, std::fstream::in | std::ios::binary);
        return true;
    }
    // clear the buffer and then read data from file
    bool ClearAndRead(void)
    {
        dataBuffer.clear();
        return ReadAndAppend();
    }
    // append to the current
    bool ReadAndAppend(void)
    {
        // get the length of the file
        if (!file) {
            std::cout << "Err, ReadBinary::ReadAndAppend, file invalid!\n";
            return false;
        }
        file.seekg(0, file.end);
        uint32_t len = file.tellg();
        file.seekg(0, file.beg);
        // calculate the amount of valid data
        uint32_t numOfLoops = len / type_size;
        for (uint32_t i = 0; i < numOfLoops; i++) {
            file.seekg(i * type_size, file.beg);
            file.read(entry.bytes, type_size);
            dataBuffer.push_back(entry.data);
        }
        return true;
    }
    // close the current file
    void Close(void)
    {
        if (!file.is_open()) {
            return;
        }
        file.close();
    }
    const std::vector<T> &GetDataBuffer(void) { return dataBuffer; }

   private:
    // file
    std::ifstream file;
    // data buffer
    std::vector<T> dataBuffer;
    // entry buffer
    union {
        T data;
        char bytes[type_size];
    } entry;
};

};  // namespace FileIO

#endif