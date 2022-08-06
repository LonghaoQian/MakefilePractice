#include <iostream>
#include "test_module_0.h"

namespace ModelBuilder
{
BlockBuilderA::BlockBuilderA() {}
BlockBuilderA::~BlockBuilderA() {}
void BlockBuilderA::AddBlock()
{
    std::cout << "module 0 is added! \n";
}
}  // namespace ModelBuilder