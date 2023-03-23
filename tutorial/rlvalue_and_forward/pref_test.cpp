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