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

// test for async, future, promise

#include <iostream>
#include <vector>
#include <chrono>
#include <future>
#include <mutex>

int Add(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return a + b;
}

void SystemInit(void)
{
    std::cout<<"system init \n";
}

void SystemInitOnce(void)
{
    static std::once_flag flag; // must use static variable for this flag
    std::call_once(flag, SystemInit);
}

int main(void)
{
    int a = 1;
    int b = 2;
    std::future<int> res = std::async(std::launch::async, [&a, &b](){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        return a + b;
    });
    res.wait();
    std::cout<<"result is: "<<res.get()<<'\n';
    SystemInitOnce();
    SystemInitOnce();

    std::promise<int> p;
    auto fut1 = p.get_future();
    std::thread th2([](std::promise<int>&& p) {
        p.set_value(3);
    }, std::move(p));
    fut1.wait();
    std::cout<<fut1.get()<<'\n';
    th2.join();
    return 0;
}