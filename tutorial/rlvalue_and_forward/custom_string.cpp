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