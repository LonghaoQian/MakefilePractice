/*
 * register singleton
 */
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