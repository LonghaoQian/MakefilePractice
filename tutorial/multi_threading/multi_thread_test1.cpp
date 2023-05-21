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

// test lock and condition variable

#include <iostream>
#include <vector>
#include <thread>
#include <condition_variable>

std::mutex gLock;
std::condition_variable gConditionVariable;

int main(void)
{
    int result = 42;
    bool notified = false;
    // Reporting thread
    // must wait work done by working thread
    std::thread reporter([&]{
        std::unique_lock<std::mutex> lock(gLock);
        if(!notified) {
            gConditionVariable.wait(lock);
        }
        std::cout<<"reporter, result is: "<<result<<'\n';
    });
    // Working thread
    std::thread worker([&] {
        std::unique_lock<std::mutex> lock(gLock);
        // Do our work, because we have the lock
        result = 42 + 5;
        notified = true;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout<<"worker complete! \n";
        // wake up a thread, that is waiting, for some conditions to be true
        gConditionVariable.notify_one();
    });
    reporter.join();
    worker.join();
    std::cout<<"program complete! \n";
    return 0;
}