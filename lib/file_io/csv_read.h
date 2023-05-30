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
#ifndef CSV_READ_H
#define CSV_READ_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

namespace File_IO
{
    template <typename T>
    using CsvContent = std::vector<std::vector<T>>;
    using OpenMode =  std::ios::ios_base::openmode; // app for append, trunc for overwrite
    CsvContent<std::string> GetFromCsv(const char* fileName);

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
};

#endif