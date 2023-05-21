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

// test msg queue

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>
#include "msg_queue.h"

int main(void)
{
    ThreadSafeQueue<uint32_t> msgQueue;
    std::vector<uint32_t> data = { 0, 2, 4, 5, 7 };

    std::thread consumer([&](void){
        bool flag = true;
        while(flag) {
            uint32_t temp;
            msgQueue.WaitAndPop(temp);
            std::cout<<"get value: "<<temp<<'\n';
            if (temp == data.back()) {
                flag = false;
                std::cout<<"exit... \n";
            }
        }
    });
    std::cout<<"consumer started! \n";
    // wait for 1 second
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // start producer
    std::thread producer([&](void){
        for(auto& t : data) {
            msgQueue.Push(t);
        }
    });
    std::cout<<"producer started! \n";
    producer.join();
    consumer.join();
    return 0;
}