/*************************************************************

MIT License

Copyright (c) 2024 Dr. Longhao Qian

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

// operator overload precedence
// overloaded operator will keep the original precedence
// evaluation of the expression is done from the right to the left
#include <iostream>
#include <string_view>
#include <string>

class TestOverload {
    public:
    TestOverload(std::string_view name, double val) {
        name_ = name;
        val_ = val;
    }
    ~TestOverload() = default;
    TestOverload& Add(TestOverload& other) {
        std::cout<<name_<<" add "<< other.name_<<'\n';
        return *this;
    };
    TestOverload& Product(TestOverload& other) {
        std::cout<<name_<<" times "<< other.name_<<'\n';
        return *this;
    };
    std::string name_;
    TestOverload& operator+(TestOverload& other) { return Add(other); };
    TestOverload& operator*(TestOverload& other) { return Product(other); };
    double val_;
};

int main(void)
{
    TestOverload a("a", 0.0);
    TestOverload b("b", 1.2);
    TestOverload c("c", 3.3);
    TestOverload d("d", -0.2);
    TestOverload e("e", 5.0);
    a + b * (c + d) + a * e;
    return 0;
}