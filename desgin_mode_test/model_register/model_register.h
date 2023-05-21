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

#ifndef MODEL_REGISTER
#define MODEL_REGISTER

#include <functional>
#include <map>
#include <memory>
#include "module_base.h"
#include "parameter.h"

using ModuleCreateFunc = std::function<std::unique_ptr<ModuleBase>(const ParaPtr&)>;

class ModelFactory {
public:
    ModelFactory() = default;
    ~ModelFactory() = default;
    static ModelFactory& Instance();
    void ResigerFunc(unsigned int index, ModuleCreateFunc& func);
    ModuleCreateFunc& GetCreateFunc(unsigned int index);
private:
    std::map<unsigned int, ModuleCreateFunc> container;
    ModuleCreateFunc invalidFunc{nullptr};
};

class RegistModelCreateFunc {
public:
    RegistModelCreateFunc(unsigned int index, ModuleCreateFunc func) {
        ModelFactory::Instance().ResigerFunc(index, func);
    }
};

#define REG_MODEL_CREATE_FUNC(index, className) \
    static RegistModelCreateFunc g_resiger##className##func(index, \
    [](const ParaPtr& ptr) { return std::make_unique<className>(ptr); });

#endif