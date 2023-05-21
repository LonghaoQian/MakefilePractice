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

#include <iostream>
#include <thread>
#include <string>
#include <chrono>

class MyTread
{
public:
    // thread entry point
    void Main()
    {
        std::cout<<"my thread main: "<<name<<" : "<<age<<'\n';
    }
    std::string name;
    int age = 100;
};

class XThread
{
public:
    virtual void Start()
    {
        th = std::thread(&XThread::Main, this);
    }
    virtual void Stop()
    {
        isExit = true;
        Wait();
    }
    virtual void Wait()
    {
        if(th.joinable()) {
            th.join();
        }
    }
    virtual void Main(void) = 0;
    bool IsExit(void) {
        return isExit;
    }
private:
    std::thread th;
    bool isExit{false};
};

class TestXTread : public XThread
{
public:
    void Main() override
    {
        std::cout<<"TestXThread Main \n";
        while (!IsExit()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout<<" . "<<std::flush;
        }
    }
    std::string name;
};

class TestLambda
{
public:
    void Start()
    {
        std::thread th([this](){ std::cout<<"name = "<<this->name<<'\n'; });
        th.join();
    }

    std::string name = "test lambda";
};

int main(void)
{
    std::thread th(
        [](int i) { std::cout<<"test lambda "<<i<<'\n'; },
        123
    );
    th.join();
    TestLambda test;
    test.Start();

    MyTread myth;
    myth.name = "test name 001";
    myth.age = 30;
    std::thread th1(&MyTread::Main, &myth);
    th1.join();

    TestXTread testth;
    testth.name = "testxthread name";
    testth.Start();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    testth.Stop();
    return 0;
}