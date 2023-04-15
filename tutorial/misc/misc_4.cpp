/*************************************************************

Copyright(C) 2023 Longhao Qian

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

// placement new and mutable keyword


// PROGRAM 1
#include <iostream>
using std::cout;
/*
class Test {
public:
  int x;
  mutable int y;
  Test() { x = 4; y = 10; }
};
*/

// PROGRAM 2
class Test {
public:
  int x;
  mutable int y;
  Test() { x = 4; y = 10; }
};


int main(void)
{
    const Test t1;
   // t1.x = 8; won't compile
    t1.y = 20;
    cout << t1.y<<'\n';
    return 0;
}