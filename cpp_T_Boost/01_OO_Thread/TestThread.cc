#include "Thread.h"
#include <unistd.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyThread
: public Thread
{
public:
    MyThread() = default;//C++11

private:
    void run() override
    {
        while(1)
        {
            cout << "MyThread is running!" << endl;
            sleep(1);
        }
    }
};

void test()
{
    MyThread mt;
    mt.start();

    mt.stop();
}

void test2()
{
    MyThread *pmt = new MyThread();
    pmt->start();

    pmt->stop();
}

void test3()
{
    unique_ptr<Thread> pth1(new MyThread());
    pth1->start();

    pth1->stop();
}

int main(int argc, char *argv[])
{
    test3();
    return 0;
}

