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