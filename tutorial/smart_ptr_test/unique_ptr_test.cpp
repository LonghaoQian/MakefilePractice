/*************************************************************

Copyright(C) 2023 Longhao Qian

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