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