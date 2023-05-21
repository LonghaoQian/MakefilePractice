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

#include <memory>
#include <iostream>
#include <string>

struct Resource {
    // ..some stuff , expensive to reallocate in memory..
    bool isFree{true};
};

constexpr uint32_t POOL_SIZE = 5;

class Pool {
public:
    Pool() = default;
/*
    // using functor
    struct Deleter {
        void operator()(Resource *r) {
            if(r != nullptr) {
                r->isFree = true; // mark the resource as free
            }
        }
    };
*/

    // return a unique ptr
    auto Get(void) {
        // unique ptr with custom deleter
        auto Deleter = [](Resource *r) {
            if(r != nullptr) {
                r->isFree = true; // mark the resource as free
            }
        };
        // auto rp = std::unique_ptr<Resource, Deleter>(nullptr, Deleter());
        auto rp = std::unique_ptr<Resource, decltype(Deleter)>(nullptr, Deleter); // using lambda function
        // find the first free resource
        for(auto& t : resource) {
            if (t.isFree) {
                t.isFree = false;
                rp.reset(&t);
                break;
            }
        }
        return rp;
    }
    // display resource availability
    void DispAvail(void) {
        std::cout<<"------------\n";
        for (uint32_t i = 0; i < POOL_SIZE; i++) {
            if (resource[i].isFree) {
                std::cout<<"resouce #"<<i<<" is free\n";
            } else {
                std::cout<<"resouce #"<<i<<" is inUse\n";
            }
        }
    }
private:
    Resource resource[POOL_SIZE]; // resource cache
};

int main(void)
{
    Pool pool1;
    {
        auto res1 = pool1.Get();
        pool1.DispAvail();
        auto res2 = pool1.Get();
        pool1.DispAvail();        
    }
    pool1.DispAvail();
    return 0;
}