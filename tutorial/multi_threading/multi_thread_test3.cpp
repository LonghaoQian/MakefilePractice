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