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

#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H

#include <vector>
#include <memory>
#include "module_base.h"

class ModelManager {
public:
    ModelManager() = default;
    ~ModelManager() = default;
    void Preprocess(void);
    void ConnectModule(void);
    void AddModule(ModuleBasePtr& moduelPtr);
    void ResetAllModule(void);
    std::vector<ModuleBasePtr>::iterator begin(void);
    std::vector<ModuleBasePtr>::iterator end(void);
    bool empty(void);
private:
    std::vector<ModuleBasePtr> moduleContainer;
};

#endif