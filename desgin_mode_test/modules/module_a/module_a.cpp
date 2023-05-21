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
#include "module_a.h"
#include "model_register.h"

REG_MODEL_CREATE_FUNC(0, ModuleA)

ModuleA::ModuleA(const ParaPtr& ptr)
{
    ParsePara(ptr);
}

bool ModuleA::ParsePara(const ParaPtr& ptr)
{
    std::string name = "add";
    auto res = GetParaData(ptr, name, 0);
    return true;
}

void ModuleA::FuncA(void)
{
    std::cout<<"module A func a\n";
}

void ModuleA::FuncB(void)
{
    std::cout<<"module A func b\n";
}

void ModuleA::FuncC(void)
{
    std::cout<<"module A func c\n";
}