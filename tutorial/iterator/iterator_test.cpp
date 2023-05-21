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

// customized iterator

#include <iterator>
#include <iostream>
#include <algorithm>

constexpr size_t DEFAULT_SIZE = 10;
template <size_t n = DEFAULT_SIZE>
class Integers
{
public: 
    struct Iterator
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = int32_t;
        using pointer = int32_t*;
        using reference = int32_t&;
        Iterator(pointer ptr) : m_ptr(ptr) {}
        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        // prefix increment
        Iterator& operator++() { m_ptr++; return *this; }
        // postfix increment
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer m_ptr{nullptr};
    };
    Iterator begin(void) { return Iterator(&m_data[0]); }
    Iterator end(void) { return Iterator(&m_data[n]); }
private:
    int m_data[n]{0};
};

int main(void)
{
    Integers<20> integers;
    // use algorithm to modify custom container
    std::fill(integers.begin(), integers.end(), 3);
    // range-based for loop
    for (auto i : integers) {
        std::cout<< i << '\n';
    }
    return 0;
}