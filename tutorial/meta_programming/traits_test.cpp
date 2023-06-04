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

// some practice example of traits

#include <iostream>

template <typename T>
struct is_a_custom_type
{
    static const bool value = false; // by default, this is false
};

template<>
struct is_a_custom_type<int>
{
    static const bool value = true; // a specialization of the template is true
};

template <typename T> 
struct is_pointer
{
    static const bool value = false;
};

template <typename T> 
struct is_pointer<T *>
{
    static const bool value = true; // specialized as a pointer
};

template<bool b>
struct algorithm_selector
{
    template <typename T>
    static void implementation([[maybe_unused]] T& object)
    {
        std::cout<<"default algorithm is called\n";
    }
};

template<>
struct algorithm_selector<true>
{
    template <typename T>
    static void implementation(T& object)
    {
        object.optimized_implementation();
    }
};

class A {};

class B {
public:
    void optimized_implementation() {
        std::cout<<"optimized algorithm is called\n";
    }
};

template<typename T>
struct support_optimised_implementation
{
    static const bool value = false; // default is not supported
};

template<>
struct support_optimised_implementation<B>
{
    static const bool value = true; // specialized for B
};

template <typename T>
void algorithm(T& object)
{
    algorithm_selector<support_optimised_implementation<T>::value>::implementation(object);
};


int main(void)
{
    std::cout<<"is void? "<<is_a_custom_type<void>::value<<"\n";
    std::cout<<"is int? "<<is_a_custom_type<int>::value<<"\n";
    std::cout<<"is int a pointer? "<<is_pointer<int>::value<<"\n";
    std::cout<<"is int* a pointer? "<<is_pointer<int*>::value<<"\n";

    // calling algorithm
    A objectA;
    B objectB;
    algorithm(objectA);
    algorithm(objectB);
    return 0;
}