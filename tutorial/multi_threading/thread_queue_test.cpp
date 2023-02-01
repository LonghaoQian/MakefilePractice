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