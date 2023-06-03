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
#ifndef CSV_PROC_H
#define CSV_PROC_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
namespace FileIO
{
    template <typename T>
    using CsvContent = std::vector<std::vector<T>>;
    using OpenMode =  std::ios::ios_base::openmode; // app for append, trunc for overwrite
    CsvContent<std::string> GetFromCsv(const char* fileName) {
        if (fileName == nullptr) {
            std::cout<<"ERR: invalid file name "<<'\n';
            return {};
        }
        std::vector<std::string> row;
        std::fstream file(fileName, std::ios::in);
        std::string line, word;
        if(!file.is_open()) {
            std::cout<<"ERR: Can not open file: "<<fileName<<'\n';
            return {};
        }
        std::vector<std::vector<std::string>> res;
        while(getline(file, line)) {
            row.clear();
            std::stringstream str(line);
            while(getline(str, word, ',')) {
                row.emplace_back(word);
            }
            res.emplace_back(row);
        }
        return res;
    }

    template <typename T>
    bool WriteToCsv(const char* fileName, const CsvContent<T>& content, OpenMode mode) {
        if (fileName == nullptr) {
            std::cout<<"ERR: invalid file name "<<'\n';
            return false;
        }
        // if file does not exists, create a new file
        std::fstream file(fileName, mode | std::fstream::out);
        std::stringstream temp;
        for (auto it = content.begin(); it != content.end(); it++) {
            temp.str("");
            copy((*it).begin(), (*it).end(), std::ostream_iterator<T>(temp, ","));
            file<<temp.str()<<'\n';
        }
        return true;
    }

    // default is double
    template<class T>
    inline T ConvertString(const std::string& input) {
        std::cout<<"defualt is used!\n";
        return std::stod(input);
    }

    template<>
    inline double ConvertString<double>(const std::string& input) {
        return std::stod(input);
    }

    template<>
    inline float ConvertString<float>(const std::string& input) {
        return std::stof(input);
    }

    template<>
    inline long double ConvertString<long double>(const std::string& input) {
        return std::stold(input);
    }

    template<>
    inline int ConvertString<int>(const std::string& input) {
        return std::stoi(input);
    }

    template<>
    inline long int ConvertString<long int>(const std::string& input) {
        return std::stoll(input);
    }

    template<>
    inline unsigned int ConvertString<unsigned int>(const std::string& input) {
        return std::stoul(input);
    }

    template<>
    inline unsigned long int ConvertString<unsigned long int>(const std::string& input) {
        return std::stoull(input);
    }

    using CsvContentItr = CsvContent<std::string>::iterator;
    template <typename T>
    CsvContent<T> ConvertCsv(CsvContentItr beginItr, CsvContentItr endItr)
    {
        CsvContent<T> res;
        res.reserve(static_cast<size_t>(std::distance(beginItr, endItr)));
        std::for_each(beginItr, endItr, [&res](const std::vector<std::string>& a) {
            res.push_back({});
            std::for_each(a.begin(), a.end(), [&res](const std::string& b) {
                res.back().push_back(ConvertString<T>(b));
            });
        });
        return res;
    }
};

#endif