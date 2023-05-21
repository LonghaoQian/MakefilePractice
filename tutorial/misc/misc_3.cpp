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