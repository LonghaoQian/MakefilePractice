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

// auto keyword and template programming

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

template<typename T>
void Func(const T& c)
{
    // ADL
    // 依赖参数查找
    using std::begin;
    using std::end;
    for (auto it = begin(c), ite = end(c); it != ite; ++it) {
        std::cout<<*it<<'\n';
    }
}

int main(void)
{
    int a[10];
    for (size_t i = 0; i < 10; i++) {
        a[i] = i;
    }
    std::vector<int> b(10, 3);
    Func(a);
    Func(b);
    std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout<<std::endl;
    return 0;
}