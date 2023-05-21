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