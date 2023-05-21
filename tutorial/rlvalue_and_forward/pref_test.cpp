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

#include <iostream>
#include <functional>

class A {
public:
    A(void) { }
    int Func1(int a) { return a; }
    int Func2(int b) { return b; }
};


int (A::*Amptr)(int) = &A::Func1;
using Amptr1 = int(A::*)(int);
using Ptr = std::function<int(A&, int)>;
int main(void)
{
    A a1;
    A *p1 = new A();
    (a1.*Amptr)(1);
    (p1->*Amptr)(1);
    Amptr1 ptr = &A::Func2;
    (p1->*ptr)(1);
    Ptr f1 = &A::Func1;
    f1(a1, 2);
    return 0;
}