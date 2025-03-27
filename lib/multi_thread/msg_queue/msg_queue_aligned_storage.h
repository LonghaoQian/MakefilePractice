/*************************************************************

MIT License

Copyright (c) 2025 Dr. Longhao Qian

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

// implement a ring buffer with aligned storage and displacement new
// the size of buffer should be power of 2 for optimal index 
// calculation

#ifndef MSG_QUEUE_ALIGNED_STORAGE_H
#define MSG_QUEUE_ALIGNED_STORAGE_H

#include <thread>
#include <condition_variable>
#include <atomic>
#include <cstdlib>
#include <new>
#include <type_traits>
#include <array>
#include <memory>

template<class T, size_t Capacity>
class ThreadSafeQueueAlignedStorage {
public:
  ThreadSafeQueueAlignedStorage() : head_{0}, tail_{0}, transmissionEnd{false} {
  };
  ~ThreadSafeQueueAlignedStorage() {
    // manually destruct any objects in the buffer
    // if none POD, call the destructor
    std::lock_guard<std::mutex> lk(mut);
    while (!Empty())
    {
      Pop();
    }
  }
  ThreadSafeQueueAlignedStorage(const  ThreadSafeQueueAlignedStorage&) = delete;
  ThreadSafeQueueAlignedStorage& operator=(const  ThreadSafeQueueAlignedStorage&) = delete;

  static constexpr uint32_t CACHE_LINE_SIZE = 64; // 64-byte length cache line
  // round the padd size accroding to data type
  static constexpr std::size_t PaddedSize = ((sizeof(T) + CACHE_LINE_SIZE - 1)
    / CACHE_LINE_SIZE) * CACHE_LINE_SIZE;

  // aligned buffer
  struct PaddedSlot {
      alignas(CACHE_LINE_SIZE) std::byte data[PaddedSize];
  };

  // push using ...args to provide flexible 
  // interface so that we can directly construct, move, and copy move
  // through one template function
  template <typename ...Args>
  void Push(Args&&... args) {
    std::lock_guard<std::mutex> lk(mut);
    Emplace(std::forward<Args>(args)...);
    dataCond.notify_one();
  }

  // wait and pop
  void WaitAndPop(T& value) {
    std::unique_lock<std::mutex> lk(mut);
    dataCond.wait(lk, [this]{ return !Empty() || transmissionEnd.load(std::memory_order_acquire); });
    if (Empty()) {
      return;
    }
    value = std::move((*pointers[tail_]));
    Pop();
  }

  // try pop
  bool TryPop(T& value) {
    std::lock_guard<std::mutex> lk(mut);
    if (Empty()) {
      return false;
    }
    value = std::move((*pointers[tail_]));
    Pop();
    return true;
  }

  // try pop with predicate
  template<typename PredicateType>
  bool TryPop(T& value, PredicateType predicate) {
    std::lock_guard<std::mutex> lk(mut);
    if (Empty() || !predicate(*pointers[tail_])) {
      return false;
    }
    value = std::move((*pointers[tail_]));
    Pop();
    return true;
  }
  // batch pop with predicate
  template<typename PredicateType>
  void BatchPop(std::vector<T>& buffer, PredicateType predicate) {
    buffer.clear();
    std::lock_guard<std::mutex> lk(mut);
    while (!Empty() && predicate((*pointers[tail_]))) {
        buffer.emplace_back(std::move((*pointers[tail_])));
        Pop();
    }
  }

  // notify end of transmission
  void NotifyEndOfTransmission(void)
  {
    transmissionEnd.store(true, std::memory_order_release);
    dataCond.notify_all();
  }
  // is transmission ended
  bool IsTransmissionEnd(void) const
  {
      return transmissionEnd.load(std::memory_order_acquire);
  }

  void Clear(void) {
    std::lock_guard<std::mutex> lk(mut);
    while (!Empty()) {
      Pop();
    }
  }

private:
  // remove the front element
  void Pop(void) {
    pointers[tail_].reset();
    TailIncrement();
  }

  bool Full(void) const {
    return (head_ + 1) % Capacity == tail_;
  }

  bool Empty(void) const {
    return head_ == tail_;
  }
  // emplace: construct the object directly
  template <typename ...Args>
  void Emplace(Args&&... args) {
    if (Full()) {
      // if full, then ditch the oldest element
      Pop();
    }
    // placement new at the head of the data
    pointers[head_].reset(new (&buffer[head_].data) T(std::forward<Args>(args)...));
    // update the head index
    HeadIncrement();
    // std::cout<<"queue size:"<< <<'\n';
  }
  void HeadIncrement(void) {
    head_ = (head_ + 1) % Capacity;
  }
  void TailIncrement(void) {
    tail_ = (tail_ + 1) % Capacity;
  }
  std::array<PaddedSlot, Capacity> buffer;
  // define the custom deleter used in unique_ptr
  struct PlacementDeleter {
    void operator()(T* ptr) const noexcept {
      if (ptr) {
        ptr->~T();
      }
    }
  };
  // further improvement: use aligned storage for the following:
  std::array<std::unique_ptr<T, PlacementDeleter>, Capacity> pointers;
  mutable std::mutex mut;
  std::condition_variable dataCond;
  uint32_t head_{0};
  uint32_t tail_{0};
  std::atomic<bool> transmissionEnd{false};
};
#endif