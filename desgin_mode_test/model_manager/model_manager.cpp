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
#include <utility>
#include "model_manager.h"

void ModelManager::AddModule(ModuleBasePtr& moduelPtr)
{
    moduleContainer.emplace_back(std::move(moduelPtr));
}

void ModelManager::ResetAllModule(void)
{
    for (auto itr = begin(); itr != end(); itr++) {
        if ((*itr) != nullptr) {
            (*itr)->FuncA();
        }
    }
}

std::vector<ModuleBasePtr>::iterator ModelManager::begin(void)
{
    return moduleContainer.begin();
}

std::vector<ModuleBasePtr>::iterator ModelManager::end(void)
{
    return moduleContainer.end();
}

bool ModelManager::empty(void)
{
    return moduleContainer.empty();
}