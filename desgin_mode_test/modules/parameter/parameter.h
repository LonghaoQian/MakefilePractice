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

#ifndef PARAMETER_H
#define PARAMETER_H

#include <vector>
#include <memory>
#include <string>

struct ModelPara;

using ParaPtr = std::unique_ptr<ModelPara>;

// store parameters in a linked list
struct ModelPara {
    std::string name; // current field name
    unsigned int level{0}; // current level of the tree
    std::vector<double> data{0}; // data field
    std::vector<ParaPtr> child; // pointers to child field
};

std::vector<double> GetParaData(const ParaPtr& paraPtr, const std::string& name, unsigned int level);

#endif