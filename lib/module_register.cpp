#include "module_register.h" 
#include <iostream>

namespace ModelBuilder {

    BlockBuilderBase::BlockBuilderBase()
    {

    }

    BlockBuilderBase::~BlockBuilderBase()
    {

    }

    BlockResiger::BlockResiger()
    {
        // registor function table
        std::cout<<"resgister constructor is called. \n";
    }
    BlockResiger::~BlockResiger()
    {
        for (auto it = funcList.begin(); it != funcList.end(); it++) {
            delete it->second;
        }
    }
    BlockResiger& BlockResiger::CheckFuncList()
    {
        static BlockResiger br;
        return br;
    }
    void BlockResiger::CallFuncList(int idx)
    {
        if (funcList.empty()) {
            std::cout<<"no method to call! \n";
            return;
        }
        funcList[idx]->AddBlock();
    }
    void BlockResiger::AddToFuncList(int idx, BlockBuilderBase *func)
    {
        funcList[idx] = func;
    }
}