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