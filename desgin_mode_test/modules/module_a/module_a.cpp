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