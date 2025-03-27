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

#ifndef MSG_QUEUE_H
#define MSG_QUEUE_H

#include <thread>
#include <condition_variable>
#include <queue>
#include <vector>
#include <atomic>

template<class T, size_t bufferSize>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() = default;
    ~ThreadSafeQueue() = default;
    ThreadSafeQueue(const ThreadSafeQueue&) = delete;
    ThreadSafeQueue& operator=(const ThreadSafeQueue&) = delete;

    void Push(const T& new_value) {
        std::lock_guard<std::mutex> lk(mut);
        if (dataQueue.size() >= bufferSize) {
          dataQueue.pop();
        }
        dataQueue.push(new_value);
        dataCond.notify_one();
    }

    void Push(T&& new_value) {
        std::lock_guard<std::mutex> lk(mut);
        if (dataQueue.size() >= bufferSize) {
          dataQueue.pop();
        }
        dataQueue.push(std::move(new_value));
        dataCond.notify_one();
    }

    void WaitAndPop(T& value) {
        std::unique_lock<std::mutex> lk(mut);
        dataCond.wait(lk, [this]{ return !dataQueue.empty() || transmissionEnd.load(std::memory_order_acquire); });
        
        if (!dataQueue.empty()) {
            value = std::move(dataQueue.front());
            dataQueue.pop();
        }
    }

    bool TryPop(T& value) {
        std::lock_guard<std::mutex> lk(mut);
        if (dataQueue.empty()) return false;
        
        value = std::move(dataQueue.front());
        dataQueue.pop();
        return true;
    }

    // Pop if additional criteria are matched
    template<typename PredicateType>
    bool TryPop(T& value, PredicateType predicate) {
        std::lock_guard<std::mutex> lk(mut);
        if (dataQueue.empty() || !predicate(dataQueue.front())) {
            return false;
        }
        value = std::move(dataQueue.front());
        dataQueue.pop();
        return true;
    }

    // Batch pop if additional criteria are matched
    template<typename PredicateType>
    void BatchPop(std::vector<T>& buffer, PredicateType predicate) {
        buffer.clear();
        std::lock_guard<std::mutex> lk(mut);
        while (!dataQueue.empty() && predicate(dataQueue.front())) {
            buffer.emplace_back(std::move(dataQueue.front()));
            dataQueue.pop();
        }
    }

    bool Empty() const {
        std::lock_guard<std::mutex> lk(mut);
        return dataQueue.empty();
    }

    void NotifyEndOfTransmission() {
        transmissionEnd.store(true, std::memory_order_release);
        dataCond.notify_all();
    }

    bool IsTransmissionEnd() const {
        return transmissionEnd.load(std::memory_order_acquire);
    }

private:
    mutable std::mutex mut;
    std::queue<T> dataQueue;
    std::condition_variable dataCond;
    std::atomic<bool> transmissionEnd{false};
};
#endif