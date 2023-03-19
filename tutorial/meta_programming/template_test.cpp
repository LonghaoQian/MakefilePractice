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

// template programming test

#include <iostream>
#include <vector>
#include <array>

int Func1(int b1, int b2)
{
    return b1 - b2;
}

template <typename T1, typename T2>
T1 Func1(T1 b1, T2 b2)
{
    return b1 + b2;
}

template <typename T>
T Func2(T b1, T b2)
{
    return b1 + b2;
}

// template with parameter
constexpr size_t DEFAULT_SIZE = 16;
constexpr size_t DYNAMIC_SIZE = 0;
// general container using fixed size array
template <typename T, size_t n = DEFAULT_SIZE>
class Container
{
public:
    explicit Container(void) {
        std::cout<<"container with fixed size is used!\n";
    }
    void PushBack(T&& input) {
        if (currSize >= maxSize) {
            return;
        }
        currSize++;
        data[currSize - 1] = std::forward<T>(input);
    }
    T& operator[](size_t i) {
        return data[i];
    }
    void PopBack(void) {
        if (currSize != 0) {
            currSize--;
        }
    }
private:
    std::array<T, n> data;
    std::size_t currSize = 0; // actual size
    std::size_t maxSize = n; // max size
};

// specialization: dynamic size container
template<typename T>
class Container<T, DYNAMIC_SIZE> {
public:
    explicit Container(void) {
        std::cout<<"container with dynamic size is used!\n";
    }
    void PushBack(T&& input) {
        data.push_back(std::forward<T>(input));
    }
    T& operator[](size_t i) {
        return data[i];
    }
    void PopBack(void) {
        data.pop_back();
    }
    size_t GetSize(void) {
        return data.size();
    }
private:
    std::vector<T> data;
};

int main(void)
{
    int res1 = Func1(1, 2.0); // ok
    int res2 = Func1(2.0, 2.0); // ok
    int res3 = Func2(2.0, 2.0); // ok, return type force converted to int
    // int res4 = Func2(1, 2.0); // error, type mismatch
    int res4 = Func1(1, 1); // will use non-template function first
    std::cout<<res1<<'\n';
    std::cout<<res2<<'\n';
    std::cout<<res3<<'\n';
    std::cout<<res4<<'\n'; // returns zero

    Container<int> p1;
    p1.PushBack(3);
    p1.PushBack(4);
    std::cout<<p1[0]<<'\n';
    std::cout<<p1[1]<<'\n';
    Container<int, DYNAMIC_SIZE> p2;
    p2.PushBack(5);
    p2.PushBack(10);
    std::cout<<p2[0]<<'\n';
    std::cout<<p2[1]<<'\n';
    std::cout<<p2.GetSize()<<'\n';
    return 0;
}