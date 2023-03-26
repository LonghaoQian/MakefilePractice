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

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cstdint>
#include <tuple>
#include <string>


template <typename T>
using MyVector = std::vector<T>;

template <template <typename> class Container>
void Foo(const Container<int>& v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout<<std::endl;
}

enum class EN : std::uint8_t {
    CHOICE_1,
    CHOICE_2
};

struct PersonInfo {
    std::string name;
    std::string id_num;
    int birtch_year;
};

// compare struct only using some of the elments
bool operator<(const PersonInfo &lhs, const PersonInfo &rhs)
{
    return std::tie(lhs.name, lhs.id_num) < std::tie(rhs.name, rhs.id_num);
}

using my_tuple  = std::tuple<int, std::string, std::string>;

int main(void)
{
    MyVector<int> v1{1, 3, 4};
    Foo<MyVector>(v1);
    EN r = EN::CHOICE_1;
    switch (r) {
        case EN::CHOICE_1 : std::cout<<"choice 1\n"; break;
        case EN::CHOICE_2 : std::cout<<"choice 2\n"; break;
    }
    std::vector<my_tuple> vn{{1, "one", "un"}};
    std::get<2>(vn[0]) = "une";
    my_tuple two{2, "two", "deux"};
    int num;
    std::string french;
    std::tie(num, std::ignore, french) = two;
    std::cout<<french<<'\n';
    PersonInfo info0{};
    //auto [a0, a1, a2] = info0;
    //std::cout<<a2<<'\n';
    return 0;
}