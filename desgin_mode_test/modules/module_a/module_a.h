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

#ifndef MODULE_A_H
#define MODULE_A_H

#include "module_base.h"
#include "parameter.h"

class ModuleA : public ModuleBase {
public:
    explicit ModuleA(const ParaPtr& ptr);
    ~ModuleA() = default;
    void FuncA(void) override;
    void FuncB(void) override;
    void FuncC(void) override;
private:
    bool ParsePara(const ParaPtr& ptr);
};

#endif