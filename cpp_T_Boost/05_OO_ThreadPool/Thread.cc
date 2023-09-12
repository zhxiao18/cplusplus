#include "Thread.h"
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

Thread::Thread()
: _thid(0)
, _isRunning(false)
{

}

Thread::~Thread()
{

}

//线程开始与结束
void Thread::start()
{
    //pthread_create第三个参数的返回类型与函数类型是严格确定的
    //也就是第三个参数的函数类型已经确定，不能更改
    /* int ret = pthread_create(&_thid, nullptr, threadFunc, nullptr); */
    int ret = pthread_create(&_thid, nullptr, threadFunc, this);
    if(ret)
    {
        perror("pthread_create");
        return;
    }

    _isRunning = true;
}

void Thread::stop()
{
    if(_isRunning)
    {
        int ret = pthread_join(_thid, nullptr);
        if(ret)
        {
            perror("pthread_join");
            return;
        }

        _isRunning = false;
    }
}

//线程入口函数
void *Thread::threadFunc(void *arg)
{
    //就应该执行任务
    Thread *pth = static_cast<Thread *>(arg);
    if(pth)
    {
        pth->run();//多态
    }
    else
    {
        cout << "pth == nullptr" << endl;
    }

    /* return nullptr; */
    pthread_exit(nullptr);
}

