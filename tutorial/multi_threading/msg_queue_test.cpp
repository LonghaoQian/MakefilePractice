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