/*************************************************************

Copyright(C) 2023 Longhao Qian

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

// test the effect of compiler optimization
#include <iostream>
#include <vector>
#include <chrono>
#include <iterator>
#include <algorithm>
#include <random>

int main(void)
{
    std::vector<int32_t> a(10, 3);
    std::copy(a.begin(), a.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << '\n';

    // sort a random sequence
    constexpr uint32_t SIZE = 1000000; // 1 million random numbers
    std::vector<int32_t> b;
    b.reserve(SIZE);
    std::default_random_engine generator;
    std::uniform_int_distribution<int32_t> distrubution(1, 100);
    for (uint32_t i = 0; i < SIZE; i++)
    {
        b.emplace_back(distrubution(generator));
    }
    auto t1 = std::chrono::steady_clock::now();
    std::sort(b.begin(), b.end(), std::greater<int32_t>());
    auto t2 = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " ns has passed.\n";
    return 0;
}