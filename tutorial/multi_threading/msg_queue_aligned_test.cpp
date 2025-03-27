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

// test msg queue with aligned storage

#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>
#include <chrono>
#include "msg_queue_aligned_storage.h"
#include <atomic>

struct Frame {
    double data{0.0};
    uint32_t frameId{0};
    Frame(double data_, uint32_t frameId_)
    {
        data = data_;
        frameId = frameId_;
    }
};
class TestStruct {
    public:
    TestStruct() = default;
    ~TestStruct() = default;
    // redefine copy constructor
    TestStruct(const TestStruct& other) : data(other.data) {
    };
    TestStruct& operator=(const TestStruct& other) {
        if (this == &other) {
            return *this;
        }
        data = other.data;
        return *this;
    };
    TestStruct(TestStruct&& other) noexcept
    : data(std::move(other.data)){
        other.data.clear();
        std::cout<<"move constructor is called\n";
    };
    TestStruct& operator=(TestStruct&& other) {
        if(this == &other) {
            return *this;
        }
        data.clear();
        data = std::move(other.data);
        other.data.clear();
        std::cout<<"move assignment is called\n";
    };
    // data array
    std::vector<Frame> data;
};

std::atomic<bool> g_consumerOK{false};

int main(void)
{
    
    ThreadSafeQueueAlignedStorage<Frame, 64> msgQueue;
    std::vector<Frame> data;

    ThreadSafeQueueAlignedStorage<uint32_t, 64> timerQueue;
    std::vector<uint32_t>timerQ;

    data.emplace_back(0.1, 1);
    data.emplace_back(0.3, 2);
    data.emplace_back(0.0, 3);
    data.emplace_back(-0.1, 4);
    data.emplace_back(0.5, 5);

    timerQ.push_back(2);
    timerQ.push_back(2);
    timerQ.push_back(2);
    timerQ.push_back(4);
    timerQ.push_back(6);

    g_consumerOK = true;

    // start producerTime
    std::thread producerTime([&](void){
        timerQueue.Push(timerQ[0]);
        std::this_thread::sleep_for(std::chrono::seconds(3));
        for(uint32_t i = 1; i < 3; i++) {
            timerQueue.Push(timerQ[i]);
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
        for(uint32_t i = 3; i < 5; i++) {
            timerQueue.Push(timerQ[i]);
        }
        std::cout<<"producer Time ended! \n";
    });
    // start producerData
    std::thread producerData([&](void){
        std::cout<<"producer Data started! \n";
        // wait for 1 second
        for(uint32_t i = 0; i < 2;i++) {
            msgQueue.Push(std::move(data[i]));
        }
        // wait for 2 seconds
        std::this_thread::sleep_for(std::chrono::seconds(2));
        for(uint32_t i = 2; i < 5; i++) {
            msgQueue.Push(std::move(data[i]));
        }
        std::cout<<"producer Data ended! \n";
    });

    // wait for 1 second
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread consumer([&](void){
        std::cout<<"consumer started! \n";
        // define buffer
        std::vector<Frame> buffer;
        uint32_t frameId{0};
        while(g_consumerOK) {
            // clear buffer
            buffer.clear();
            // wait for timer producer
            timerQueue.WaitAndPop(frameId);
            if (timerQueue.IsTransmissionEnd()) {
                break;
            }
            std::cout<<"consumer gets time frame: "<<frameId<<'\n';
            // check data queue
            msgQueue.BatchPop(buffer, [&frameId] (const Frame& frame) {
                 return frameId > frame.frameId;
            });
            // print buffer size
            std::cout <<"curr frame id: "<<frameId<<'\n';
            std::cout<< "size of the buffer is from pop is: "<< buffer.size() <<'\n';
            // print buffer content
            for (auto& t : buffer) {
                std::cout<<"frame id:"<< t.frameId<<" data:"<<t.data<<'\n';
            }
            
        }
        std::cout<<"consumer ended! \n";
    });

    // wait for 8 seconds
    std::this_thread::sleep_for(std::chrono::seconds(8));
    timerQueue.NotifyEndOfTransmission();
    msgQueue.NotifyEndOfTransmission();
    g_consumerOK = false;

    producerData.join();
    producerTime.join();
    consumer.join();
    return 0;
}