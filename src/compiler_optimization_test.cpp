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