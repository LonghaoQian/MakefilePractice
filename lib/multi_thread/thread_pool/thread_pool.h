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

#ifndef THREAD_POOL
#define THREAD_POOL

#include <thread>
#include <condition_variable>
#include <queue>
#include <functional>
#include <memory>

// thread pool
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

// TO DO: thread pool with arguments
class ThreadPoolWithArgs {
private:
public:
};

// thread pool with time stamp consistency check

// TO DO: lock-free thread pool

#endif