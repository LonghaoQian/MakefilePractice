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

#include "module_register.h"
#include <iostream>

namespace ModelBuilder
{
BlockBuilderBase::BlockBuilderBase() {}

BlockBuilderBase::~BlockBuilderBase() {}

BlockResiger::BlockResiger()
{
    // registor function table
    std::cout << "resgister constructor is called. \n";
}
BlockResiger::~BlockResiger()
{
    for (auto it = funcList.begin(); it != funcList.end(); it++) {
        delete it->second;
    }
}
BlockResiger &BlockResiger::CheckFuncList()
{
    static BlockResiger br;
    return br;
}
void BlockResiger::CallFuncList(int idx)
{
    if (funcList.empty()) {
        std::cout << "no method to call! \n";
        return;
    }
    funcList[idx]->AddBlock();
}
void BlockResiger::AddToFuncList(int idx, BlockBuilderBase *func)
{
    funcList[idx] = func;
}
}  // namespace ModelBuilder