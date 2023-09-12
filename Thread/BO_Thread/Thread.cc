#include "Thread.h"
#include <stdio.h>

Thread::Thread(ThreadCallback && cb)
:_thid(0),
_isRunning(false),
_cb(std::move(cb))
{

}
//虚析构
Thread::~Thread()
{

}

//线程开始、结束
void Thread::start()
{
    int ret = pthread_create(&_thid, nullptr, ThreadFunc, this);
    if(ret)
    {
        perror("pthread_create");
        return;
    }
    _isRunning = true;
}

void Thread::stop()
{
    int ret = pthread_join(_thid, nullptr);
    if(ret)
    {
        perror("pthread_join");
        return;
    }
    _isRunning = false;
}

//线程入口函数
void * Thread::ThreadFunc(void * arg)
{
    Thread * pth = (Thread *)arg;
    if(pth)
    {
        //多态
        pth->_cb();
    }
    else
    {
        perror("pth == nullptr");
    }
    pthread_exit(nullptr);
}
