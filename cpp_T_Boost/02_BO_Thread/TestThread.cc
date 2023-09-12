#include "Thread.h"
#include <unistd.h>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask
{
public:
    void process()
    {
        while(1)
        {
            cout << "MyTask is running!" << endl;
            sleep(1);
        }
    }
};

void func()
{
    while(1)
    {
        cout << "func is running!" << endl;
        sleep(1);
    }

}

void test()
{
    MyTask task;

    Thread th(std::bind(&MyTask::process, &task));
    th.start();

    th.stop();
}

void test2()
{
    MyTask *ptask = new MyTask();

    Thread th(std::bind(&MyTask::process, ptask));
    th.start();

    th.stop();
}

void test3()
{
    unique_ptr<MyTask> ptask(new MyTask());
    Thread th(std::bind(&MyTask::process, ptask.get()));
    th.start();

    th.stop();
}

void test4()
{
    Thread th(std::bind(func));
    th.start();

    th.stop();
}

void test5()
{
    //func函数的形态与ThreadCallback是一样的，所以可以使用std::move
    Thread th(std::move(func));
    th.start();

    th.stop();
}
int main(int argc, char *argv[])
{
    test5();
    return 0;
}

