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

#include "csv_read.h"
#include <iostream>
#include <fstream>
#include <sstream>

namespace File_IO
{

    CsvContent GetCsvContent(const char* fileName)
    {
        std::vector<std::vector<std::string>> res;
        if (fileName == nullptr) {
            std::cout<<"ERR: invalid file name "<<'\n';
            return res;
        }
        std::vector<std::string> row;
        std::fstream file(fileName, std::ios::in);
        std::string line, word;
        if(file.is_open()) {
            while(getline(file, line)) {
                row.clear();
                std::stringstream str(line);
                while(getline(str, word, ',')) {
                    row.emplace_back(word);                    
                }
                res.emplace_back(row);
            }
        } else {
            std::cout<<"ERR: Can not open file: "<<fileName<<'\n';
        }
        return res;
    }
};