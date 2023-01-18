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

#include "msg_queue.h"
#include <vector>
template<typename T>
void ThreadSafeQueue<T>::Push(T new_value)
{
    std::lock_guard<std::mutex> lk(mut);
    dataQueue.push(std::move(new_value));
    dataCond.notify_one();
}

template<typename T>
void ThreadSafeQueue<T>::WaitAndPop(T& value)
{
    std::unique_lock<std::mutex> lk(mut);
    dataCond.wait(lk, [this]{ return !dataQueue.empty(); });
    value = std::move(dataQueue.front());
    dataQueue.pop();
}

template<typename T>
void ThreadSafeQueue<T>::TryPop(T& value)
{
    std::lock_guard<std::mutex> lk(mut);
    if(dataQueue.empty()) { return false; }
    value = std::move(dataQueue.front());
    dataQueue.pop();
}

template<typename T>
void ThreadSafeQueue<T>::Empty(void) const
{
    std::lock_guard<std::mutex> lk(mut);
    return dataQueue.empty();
}