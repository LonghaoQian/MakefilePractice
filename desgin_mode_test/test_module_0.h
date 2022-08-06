/*
* this flile containts the definition of the function 
* register
*/
#ifndef TEST_MODULE_0_H
#define TEST_MODULE_0_H

#include "module_register.h"

namespace ModelBuilder {
    class BlockBuilderA : public BlockBuilderBase {
    public:
        BlockBuilderA();
        ~BlockBuilderA();
        virtual void AddBlock() override;
    };
}

#endif