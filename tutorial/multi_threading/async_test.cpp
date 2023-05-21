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