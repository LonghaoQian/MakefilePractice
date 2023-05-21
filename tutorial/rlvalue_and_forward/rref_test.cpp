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

namespace
{
// function countre recording number of times each constructor is called
size_t consFuncCounter{0};
size_t moveFuncCounter{0};
size_t copyConsFuncCounter{0};
// test move semantics
class A
{
   public:
    explicit A(size_t size_)
    {
        p = new int[size_];
        size = size_;
        std::cout << "A constructor called! \n";
        consFuncCounter++;
    }
    ~A(void)
    {
        delete[] p;
        std::cout << "A destructor called! \n";
    }
    size_t GetSize(void) const { return size; }
    void ResetSize(void) { size = 0; }
    int &operator[](size_t index) { return p[index]; }
    int GetElement(size_t index) const
    {
        if (p == nullptr || index >= size) {
            return 0;
        }
        return p[index];
    }
    // copy constructor
    A(const A &obj)
    {
        p = new int[obj.GetSize()];
        for (size_t i = 0; i < obj.GetSize(); i++) {
            p[i] = obj.GetElement(i);
        }
        size = obj.GetSize();
        std::cout << "A copy constructor called! \n";
        copyConsFuncCounter++;
    }
    // copy assignment
    A &operator=(const A &obj)
    {
        std::cout << "A assignment called! \n";
        // check whether self replication
        if (this == &obj) {
            return *this;
        }
        // delete original data and reassign data
        delete[] p;
        size = obj.GetSize();
        p = new int[size];
        for (size_t i = 0; i < size; i++) {
            p[i] = obj.GetElement(i);
        }
        return *this;
    }

    // move constructor
    // if noexcept is not added, then it is not called when vector resizes
    A(A &&obj) noexcept
    {
        std::cout << "move constructor called\n";
        this->size = obj.GetSize();
        this->p = obj.p;
        obj.p = nullptr;
        moveFuncCounter++;
    }
    // move assignment
    A &operator=(A &&obj) noexcept
    {
        std::cout << "move assginment called\n";
        if (this == &obj) {
            return *this;
        }
        delete[] p;
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

// regular function with lvalue args only accepts lvalue as parameter
void TestFunc1(A &input)
{
    A d(input);
    std::cout << "func1 -lvalue- is called \n";
}
void TestFunc2(A &input)
{
    A d(input);
    std::cout << "func2 -lvalue- is called \n";
}
// regular function with rvalue args only accepts rvalue as parameter
void TestFunc2(A &&input)
{
    // A d(input); if forward is not used, then copy constructor is called
    A d(std::forward<A>(
        input));  // if forward is used, then move constructor is called
    std::cout << "size of d is: " << d.GetSize() << '\n';
    std::cout << "func2 -rvalue- is called \n";
}

template <typename T>
void TemplateTestFunc(T &input)
{
    T d(input);
    std::cout << "template test func -lvalue- is called \n";
}

template <typename T>
void TemplateTestFunc(T &&input)
{
    T d(input);
    std::cout << "template test func -rvalue- is called \n";
}

template <typename TT>
void TemplateTestFuncForward(TT &&input)
{
    // TestFunc2(std::forward<TT>(input));
    TT d(std::forward<TT>(
        input));  // this is the key to achieve accepting both r and l value
    std::cout << "TemplateTestFuncForward is called \n";
    std::cout << "size of d is: " << d.GetSize() << '\n';
}

}  // namespace
int main(void)
{
    A obj1(30);
    ::TestFunc2(::A(20));  // rvalue version is called
    ::TestFunc2(obj1);     // lvalue version is called
    //::TestFunc1(::A(20));  // this causes a compilation error
    ::TestFunc1(obj1);
    ::TemplateTestFunc(obj1);
    ::TemplateTestFunc(::A(20));  // although rvalue version is called here,
                                  // copy constuctor is still used
    // for universal reference to work, one must let compiler to deduce
    // parameter
    ::TemplateTestFuncForward(obj1);
    ::TemplateTestFuncForward(::A(20));
    // test move semantics with containers
    std::vector<::A> containerA;
    // containerA.reserve(3);
    // containerA.push_back(A(20));
    // containerA.push_back(A(40));
    // containerA.push_back(A(30));
    // containerA.emplace_back(A(20));
    // containerA.emplace_back(A(40));
    // containerA.emplace_back(A(30));
    containerA.emplace_back(20);
    containerA.emplace_back(40);
    containerA.emplace_back(30);
    std::cout << "construct func called " << ::consFuncCounter
              << ", move constructor func called " << ::moveFuncCounter
              << ", copy constructor called " << copyConsFuncCounter << '\n';
    return 0;
}
