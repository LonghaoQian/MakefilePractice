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

#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <vector>
#include <memory>
#include "module_base.h"

class ModelManager {
public:
    ModelManager() = default;
    ~ModelManager() = default;
    void Preprocess(void);
    void ConnectModule(void);
    void AddModule(ModuleBasePtr& moduelPtr);
    void ResetAllModule(void);
    std::vector<ModuleBasePtr>::iterator begin(void);
    std::vector<ModuleBasePtr>::iterator end(void);
    bool empty(void);
private:
    std::vector<ModuleBasePtr> moduleContainer;
};

#endif