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