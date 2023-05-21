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

// test packed task

#include <iostream>
#include <future>
#include <string>
#include <chrono>
#include <thread>
#include <functional>
#include <type_traits>

int TestFunc(int a, int b, int& c)
{
    return a + b - c;
}


int TestFunc2(float a, double b, char c)
{
    return a + b - c;
}

template <typename T, typename ...Args>
void ProcFunc(std::function<T(Args ...)>&& ptr, Args &&... args)
{
    using Task = std::function<T(Args ...)>;
    std::packaged_task<T(Args ...)> t1(std::forward<Task>(ptr));
    auto fut = t1.get_future();
    std::thread th1 = std::thread(std::move(t1), std::forward<Args>(args)...);
    auto res = fut.get();
    th1.join();
    std::cout<<res<<'\n';
}


int main(void)
{
    // define a packed task
    std::function<int(int, int, int&)> f1(TestFunc);
    using Task = std::packaged_task<int(int, int, int&)>;
    Task t1(f1);
    auto fut = t1.get_future();
    int a = 1;
    int b = 2;
    int c = 5;
    std::thread th1 = std::thread(std::move(t1), a, b, std::ref(c));
    auto res = fut.get();
    std::cout<<res<<'\n';
    th1.join();
    std::function<int(float, double, char)> f2(TestFunc2);
    ProcFunc(std::move(f2), 0.1f, static_cast<double>(b), static_cast<char>(c));
    return 0;
}