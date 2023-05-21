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

// test for template function with variable args and std bind

#include <iostream>
#include <string.h>

// traits
template <typename T>
class SigmaTraits {};
template <> class SigmaTraits<char>{
public:
    typedef int ReturnType;
};

template <> class SigmaTraits<short> {
public:
    typedef int ReturnType;
};

template <> class SigmaTraits<int> {
public:
    typedef long ReturnType;
};

template <> class SigmaTraits<unsigned int> {
public:
    typedef unsigned long ReturnType;
};

template <> class SigmaTraits<float> {
public:
    typedef double ReturnType;
};

template <typename T>
inline typename SigmaTraits<T>::ReturnType Sigma(const T *start, const T *end)
{
    typedef typename SigmaTraits<T>::ReturnType ReturnType;
    ReturnType s = ReturnType();
    while (start != end) {
        s += *start++;
    }
    return s;
}
int main(void)
{
    char szNames[] = "abd";
    std::size_t nLength = strlen(szNames);
    char* p = szNames;
    char* q = szNames + nLength;
    std::cout<<Sigma(p, q)<<'\n';
    return 0;
}