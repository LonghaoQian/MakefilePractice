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

//#include "module_register.h"
//#include "test_module_0.h"
#include <vector>
#include <iostream>
#include <memory>
//using namespace ModelBuilder;
#include <functional>
#include <map>
#include "model_register.h"
class Base {
public:
    Base() = default;
    virtual ~Base() = default;
    virtual void Disp(void) = 0;
};

class Foo : public Base {
public:
    explicit Foo(int i) { std::cout<<"Foo constructed ~"<<i<<'\n'; }
    void Disp(void) override { std::cout<<"Foo disp called ~\n"; } 
    ~Foo() = default;
};

class Bar: public Base {
public:
    explicit Bar(int i) { std::cout<<"Bar constructed ~"<<i<<'\n'; }
    void Disp(void) override { std::cout<<"Bar disp called ~\n"; } 
    ~Bar() = default;
};

using BaseCreateFunc = std::function<std::unique_ptr<Base>(int)>;

class InstanceFactory {
public:
    InstanceFactory() = default;
    ~InstanceFactory() = default;
    static InstanceFactory& Instance() { 
        static InstanceFactory factory;
        return factory;}
    void ResigerFunc(unsigned int index, BaseCreateFunc& func) {
        container[index] = func;
    }
    BaseCreateFunc& GetCreateFunc(unsigned int index) {
        return container[index];
    }
private:
    std::map<int, BaseCreateFunc> container;
};

class RegistCreaterFunc {
public:
    RegistCreaterFunc(unsigned int index, BaseCreateFunc func) {
        InstanceFactory::Instance().ResigerFunc(index, func);
    }
};

#define REG_CREATE_FUNC(index, className) \
    static RegistCreaterFunc g_resiger##className##func(index, [](int i) { return std::make_unique<className>(i); });

REG_CREATE_FUNC(0, Foo)
REG_CREATE_FUNC(1, Bar)

int main(void)
{
    // BlockResiger::CheckFuncList().AddToFuncList(0, new BlockBuilderA());
    // BlockResiger::CheckFuncList().CallFuncList(0);
    /*
    BaseCreateFunc fun1 = [](int i) { return std::make_unique<Foo>(i); };
    BaseCreateFunc fun2 = [](int i) { return std::make_unique<Bar>(i); };

    */
    auto func1 = InstanceFactory::Instance().GetCreateFunc(0);
    auto func2 = InstanceFactory::Instance().GetCreateFunc(1);
    auto res1 = func1(9);
    auto res2 = func2(10);

    res1->Disp();
    res2->Disp();

    auto para_a = std::make_unique<ModelPara>();
    auto res = ModelFactory::Instance().GetCreateFunc(0);
    if (res != nullptr) {
        auto module_a = res(para_a);
        module_a->FuncA();
        module_a->FuncB();
    } else {
        std::cout<<"fun 0 undefined !\n";
    }
    return 0;
}