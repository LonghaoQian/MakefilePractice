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

// 2-phase name lookup and compile-time polymorphism

#include <iostream>

template<typename T>
struct Base {
    void f(void) { std::cout<<"Base<T>::f"<<'\n'; }
};

template<>
struct Base<int> {
    void f(void) { std::cout<<"Base<Int>::f"<<'\n'; }
};

template<typename T>
struct Derived : Base<T> {
    void g(void) {
        std::cout<<"Derived<T>::g "<<'\n';
        this->f(); // must have 'this->' for 2-phase name lookup
    }
};

int main(void)
{
    Derived<char> d;
    d.g();
    Derived<int> f;
    f.g();
    return 0;
}