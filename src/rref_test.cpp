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
#include <vector>

namespace {
    size_t consFuncCounter{0};
    size_t moveFuncCounter{0};
    size_t copyConsFuncCounter{0};
// test move semantics
class A {
public:
    explicit A(size_t size_) {
        p = new int[size_];
        size = size_;
        std::cout<<"A constructor called! \n";
        consFuncCounter++;
    }
    ~A(void) {
        delete [] p;
        std::cout<<"A destructor called! \n";
    }
    size_t GetSize(void) const {
        return size;
    }
    void ResetSize(void) {
        size = 0;
    }
    int& operator[](size_t index) {
        return p[index];
    }
    int GetElement(size_t index) const {
        if (p == nullptr || index >= size) {
            return 0;
        }
        return p[index];
    }
    // copy constructor
    A(const A& obj) {
        p = new int[obj.GetSize()];
        for (size_t i = 0; i < obj.GetSize(); i++) {
            p[i] = obj.GetElement(i);
        }
        size = obj.GetSize();
        std::cout<<"A copy constructor called! \n";
        copyConsFuncCounter++;
    }
    // copy assignment
    A& operator=(const A& obj) {
        std::cout<<"A assignment called! \n";
        // check whether self replication
        if (this == &obj) {
            return *this;
        }
        // delete original data and reassign data
        delete [] p;
        size = obj.GetSize();
        p = new int[size];
        for (size_t i = 0; i < size; i++) {
            p[i] = obj.GetElement(i);
        }
        return *this;
    }

    // move constructor
    // inf noexcept is not added, then it is not called when vector resizes
    A(A&& obj) noexcept {
        std::cout<<"move constructor called\n";
        this->size = obj.GetSize();
        this->p = obj.p;
        obj.p = nullptr;
        moveFuncCounter++;
    }
    // move assignment
    A& operator=(A&& obj) noexcept {
        std::cout<<"move assginment called\n";
        if (this == &obj) {
            return *this;
        }
        delete [] p;
        this->size = obj.GetSize();
        this->p = obj.p;
        obj.p = nullptr;
        obj.ResetSize();
        return *this;
    }
    int *p{nullptr};
private:
    size_t size{0};
};

/*
A TestFunc(void)
{
    A obj1(10);
    return obj1;
}
*/
void TestFunc2(A&& input)
{
    //A d(input); if forward is not used, then copy constructor is called
    A d(std::forward<A>(input)); // if forward is used, then move constructor is called
    std::cout<<"size of d is: "<<d.GetSize()<<'\n';
}

}
int main(void)
{
    //A obj1(10);
    //obj1[0] = 3;
    //obj1[3] = 4;
    //std::cout<<obj1[0]<<" "<<obj1[3]<<'\n';
    //auto obj3 = TestFunc();
    //std::cout<<obj3.GetSize()<<'\n';
    ::TestFunc2(::A(20));
    std::vector<::A> containerA;
    // containerA.reserve(3);
    //containerA.push_back(A(20));
    //containerA.push_back(A(40));
    //containerA.push_back(A(30));
    // containerA.emplace_back(A(20));
    // containerA.emplace_back(A(40));
    // containerA.emplace_back(A(30));
    containerA.emplace_back(20);
    containerA.emplace_back(40);
    containerA.emplace_back(30);
    std::cout<<"construct func called "<<::consFuncCounter<<
        ", move constructor func called "<<::moveFuncCounter<<
        ", copy constructor called "<<copyConsFuncCounter<<'\n';
    return 0;
}
