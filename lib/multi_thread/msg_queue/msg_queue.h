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

#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <thread>
#include <condition_variable>
#include <queue>

template<typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue(void) = default;
    ~ThreadSafeQueue(void) = default;
    void Push(T new_value);
    void WaitAndPop(T& value);
    void TryPop(T& value);
    void Empty(void) const;
private:
    mutable std::mutex mut;
    std::queue<T> dataQueue;
    std::condition_variable dataCond;
};

#endif