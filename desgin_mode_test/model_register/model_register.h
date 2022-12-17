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

#ifndef MODEL_REGISTER
#define MODEL_REGISTER

#include <functional>
#include <map>
#include <memory>
#include "module_base.h"
#include "parameter.h"

using ModuleCreateFunc = std::function<std::unique_ptr<ModuleBase>(const ParaPtr&)>;

class ModelFactory {
public:
    ModelFactory() = default;
    ~ModelFactory() = default;
    static ModelFactory& Instance();
    void ResigerFunc(unsigned int index, ModuleCreateFunc& func);
    ModuleCreateFunc& GetCreateFunc(unsigned int index);
private:
    std::map<unsigned int, ModuleCreateFunc> container;
    ModuleCreateFunc invalidFunc{nullptr};
};

class RegistModelCreateFunc {
public:
    RegistModelCreateFunc(unsigned int index, ModuleCreateFunc func) {
        ModelFactory::Instance().ResigerFunc(index, func);
    }
};

#define REG_MODEL_CREATE_FUNC(index, className) \
    static RegistModelCreateFunc g_resiger##className##func(index, \
    [](const ParaPtr& ptr) { return std::make_unique<className>(ptr); });

#endif