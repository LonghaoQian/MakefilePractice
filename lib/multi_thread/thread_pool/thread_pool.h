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

#ifndef THREAD_POOL
#define THREAD_POOL

#include <thread>
#include <condition_variable>
#include <queue>
#include <functional>
#include <memory>
class ThreadPool {
private:
    struct InteralData
    {
        using Task = std::function<void()>;
        std::mutex mut;
        std::condition_variable cond;
        bool stop = false;
        std::queue<Task> tasks;
    };
public:
    explicit ThreadPool(size_t count_  = COUNT) : data(nullptr), count(count_)
    {}
    ThreadPool(ThreadPool &&) = default;
    ~ThreadPool() {
        if(data) {
            {
                std::lock_guard<std::mutex> lk(data->mut);
                data->stop = true;
            }
            data->cond.notify_all();
        }
    }
    void Init(void) {
        data = std::make_shared<InteralData>();
        for(size_t i = 0; i < count; i++) {
            std::thread([data_ = data, i]{
                std::unique_lock<std::mutex> lk(data_->mut);
                for(;;) {
                    if(!data_->tasks.empty()) {
                        auto current = std::move(data_->tasks.front());
                        data_->tasks.pop();
                        lk.unlock();
                        current();
                        lk.lock();
                    } else if (data_->stop) {
                        break;
                    } else {
                        data_->cond.wait(lk);
                    }
                }
            }).detach();
        }
    }
    template<class F>
    void Commit(F &&task) {
        {
            std::lock_guard<std::mutex> lk(data->mut);
            data->tasks.emplace(std::forward<F>(task));
        }
    }
private:
    std::shared_ptr<InteralData> data;
    const size_t count;
    static const size_t COUNT = 8;
};

#endif