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