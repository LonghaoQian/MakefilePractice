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
template <typename T>
int TypeValue = 0;

template <>
int TypeValue<int> = 9;

template<typename T>
int TypeValue<T*> = 1;

template<template <typename> class T, typename U>
int TypeValue<T<U>> = 99;

template<template <typename, typename> class T, typename U, typename V>
int TypeValue<T<U, V>> = 999;

template<bool> struct compile_time_error;
template<> struct compile_time_error<true> {};

#define STATIC_ASSERT(_Expr, _Msg)          \
    {                                       \
        compile_time_error<((_Expr) != 0)> ERROR_##_Msg;  \
        (void)ERROR_##_Msg;                 \
    }                                       \

int main(void)
{
    std::cout<<TypeValue<char><<'\n';
    std::cout<<TypeValue<int><<'\n';
    std::cout<<TypeValue<char*><<'\n';
    std::cout<<TypeValue<std::vector<int> ><<'\n'; // vector<int> has 2 template arguments! so 999
    STATIC_ASSERT(sizeof(void*)==8, requires_32_bt_platform);
    return 0;
}