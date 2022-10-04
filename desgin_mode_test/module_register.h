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

#ifndef MODULE_RESIGTER_H
#define MODULE_RESIGTER_H

#include <unordered_map>

namespace ModelBuilder
{
class BlockBuilderBase
{
   public:
    BlockBuilderBase();
    virtual ~BlockBuilderBase();
    virtual void AddBlock() = 0;
};

class BlockResiger
{
   private:
    BlockResiger();
    ~BlockResiger();
    std::unordered_map<int, BlockBuilderBase *> funcList;

   public:
    // remove default copy constructor and copy assign constructor
    BlockResiger(BlockResiger const &) = delete;
    BlockResiger &operator=(BlockResiger const &) = delete;
    static BlockResiger &CheckFuncList();
    void CallFuncList(int idx);
    void AddToFuncList(int idx, BlockBuilderBase *func);
};
}  // namespace ModelBuilder

#endif