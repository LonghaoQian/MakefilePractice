/*************************************************************

MIT License

Copyright (c) 2023 Dr. Longhao Qian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

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
#include "model_manager.h"
#include "solver.h"

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
    auto func1 = InstanceFactory::Instance().GetCreateFunc(0);
    auto func2 = InstanceFactory::Instance().GetCreateFunc(1);
    auto res1 = func1(9);
    auto res2 = func2(10);

    res1->Disp();
    res2->Disp();
    */

    ModelManager system_0;
    auto para_a = std::make_unique<ModelPara>();
    auto res = ModelFactory::Instance().GetCreateFunc(0);
    SolverPara para;
    Solver solver1(para);


    if (res != nullptr) {
        auto module_a = res(para_a);
        system_0.AddModule(module_a);
        module_a = res(para_a);
        system_0.AddModule(module_a);
        system_0.ResetAllModule();
        solver1.UpdateStep(system_0);
    } else {
        std::cout<<"fun 0 undefined !\n";
    }

    return 0;
}