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