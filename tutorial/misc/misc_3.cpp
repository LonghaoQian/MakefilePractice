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

// use explicit keyword to disable implicit construction

#include <iostream>

class MyInt
{
public:
//    explicit MyInt(int * pdNum) // if explicit keyword is added, the code won't compile
    MyInt(int * pdNum)
    {
        std::cout<<"in MyInt(int*)"<<'\n';
        pdNimPtr = pdNum;
    }
    int getMyInt() const
    {
        return *pdNimPtr;
    }
    ~MyInt(void)
    {
        std::cout<<"in ~MyInt()"<<'\n';
        if(pdNimPtr != nullptr) {
            delete pdNimPtr;
        }
    }
private:
    int *pdNimPtr{nullptr};
};

void Print(MyInt input)
{
    std::cout<<"in print_MyInt"<<'\n';
    std::cout<<input.getMyInt()<<'\n';
}

int main(void)
{
    int *pdNum = new int(666);
    Print(pdNum); // this is dangours because the temporary object created as the argument
    // is destoryed when function exits, deleting heap allocated memory.
    int *pdNewNum = new int(888);
    *pdNum = 18; // if heap allocated memory is deleted, the pointer must be set to nullptr
    // otherwise using an invalid pointer will happen.
    std::cout<<*pdNewNum<<'\n';
    return 0;
}