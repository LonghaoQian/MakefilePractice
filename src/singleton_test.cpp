#include "module_register.h"
#include "test_module_0.h"

using namespace ModelBuilder;

int main(void)
{
    // BlockResiger::CheckFuncList().AddToFuncList(0, new BlockBuilderA());
    BlockResiger::CheckFuncList().CallFuncList(0);
    return 0;
}