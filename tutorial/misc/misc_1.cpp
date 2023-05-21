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