#include "Thread.h"
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

Thread::Thread(ThreadCallback &&cb)
: _thid(0)
, _isRunning(false)
, _cb(std::move(cb))//注册回调函数
{

}

Thread::~Thread()
{

}

void Thread::start()
{
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
    Thread *pth1 = static_cast<Thread *>(arg);
    if(pth1)
    {
        pth1->_cb();//回调函数的执行
    }
    else
    {
        cout << "pth == nullptr" << endl;
    }

    pthread_exit(nullptr);//线程退出函数
}

