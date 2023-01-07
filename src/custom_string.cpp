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
#include <stdlib.h>
#include <cstring>
#include <string>

class MyString {
public:
    MyString(void):size_(0) {}
    explicit MyString(const char* input)
    {
        size_ = strlen(input);
        if (size_ == 0) {
            return;
        }
        ptr = new char[size_ + 1];
        memcpy(ptr, input, (size_ + 1u) * sizeof(char));
    }
    ~MyString(void)
    {
        delete [] ptr;
    }
    size_t size(void) const {
        return size_;
    }
    char * c_str(void) const {
        return ptr;
    }
    MyString(const MyString& obj)
    {
        size_ = obj.size();
        ptr = new char[size_ + 1];
        memcpy(ptr, obj.c_str(), (size_ + 1u) * sizeof(char));
        std::cout << "my string copy constructor called \n";
    }
    char &operator[](size_t index) { return ptr[index]; }
    MyString &operator=(const MyString& obj)
    {
        std::cout << "my string copy assignment called \n";
        if (this == &obj) {
            return *this;
        }
        // delete
        delete[] ptr;
        size_ = obj.size();
        ptr = new char[size_ + 1];
        memcpy(ptr, obj.c_str(), (size_ + 1u) * sizeof(char));
        return *this;
    }
    MyString(MyString &&obj) noexcept
    {
        this->size_ = obj.size();
        this->ptr = obj.ptr;
        obj.ptr = nullptr;
        obj.size_ = 0;
        std::cout << "my string move constructor called \n";
    }
    MyString &operator=(MyString &&obj) noexcept
    {
        std::cout << "my string move assignment called \n";
        if (this == &obj) {
            return *this;
        }
        delete[] ptr;
        this->size_ = obj.size();
        this->ptr = obj.ptr;
        obj.ptr = nullptr;
        obj.size_ = 0;
        return *this;
    }
    char* ptr{nullptr};
    size_t size_{0};
private:
};

template<typename T>
void Display2(T &input) {
    MyString d(input);
    std::cout<<"lvalue called, "<<d.c_str()<<'\n';
}

template<typename T>
void Display2(T &&input) {
    MyString d(std::forward<T>(input));
    std::cout<<"rvalue called, "<<d.c_str()<<'\n';
}

template<typename T>
void Display(T&& input)
{
    Display2(std::forward<T>(input));
}

int main(void)
{
    MyString str1{"Hello"};
    MyString str2;
    std::cout<<"str1 size: "<<str1.size()<<", content: "<<str1.c_str()<<'\n';
    Display(str1);
    Display(MyString("Bye!"));
    str2 = std::move(str1);
    std::cout<<"str2 size: "<<str2.size()<<", content: "<<str2.c_str()<<'\n';
    std::cout<<"str1 size: "<<str1.size()<<'\n';
    return 0;
}