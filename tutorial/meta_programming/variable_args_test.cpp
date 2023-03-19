/*************************************************************

Copyright(C) 2022 Longhao Qian

This program is free software; you can redistribute it and / or
modify it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program;
if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

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