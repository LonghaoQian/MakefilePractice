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

#include <chrono>
#include <iostream>
#include "thread_pool.h"

class A {
public:
    A() = default;
    ~A() = default;
    void Func(void) {
        i = i + 3;
    }
    int i{0};
};

class B {
public:
    B() = default;
    ~B() = default;
    void Func(void) {
        i = i + 5;
    }
    int i{0};
};


int main(void)
{
    ThreadPool tPool(3);
    tPool.Init();
    A a1;
    B b1;
    std::function<void()> func1 = [&a1](){ a1.Func(); };
    std::function<void()> func2 = [&b1](){ b1.Func(); };
    tPool.Commit(func1);
    tPool.Commit(func2);
    tPool.Commit(func1);
    tPool.Commit(func1);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout<<"a1 i: "<<a1.i<<'\n';
    std::cout<<"b1 i: "<<b1.i<<'\n';
    return 0;
}