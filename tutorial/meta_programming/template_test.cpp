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