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

// test for packaged task

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

void add(int a, int b, std::promise<int>&& pr)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    pr.set_value(a + b);
}

int product(int a, int b)
{
    return a * b;
}

int main(void)
{
    // packaged_task
    std::packaged_task<int(int, int)> task(product);
    std::future<int> res = task.get_future();
    std::thread workThread0(std::move(task), 2, 5);
    // promise and future
    std::promise<int> pr;
    std::future<int> fr = pr.get_future();
    std::thread workThread(add, 3, 3, std::move(pr));
    fr.wait();
    res.wait();
    std::cout<<"promise, result is: "<<fr.get()<<'\n';
    std::cout<<"packaged_task result is: "<<res.get()<<'\n';
    workThread.join();
    workThread0.join();
    return 0;
}