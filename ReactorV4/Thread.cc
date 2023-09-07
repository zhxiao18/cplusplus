#include "Thread.h"
#include <stdio.h>

Thread::Thread(ThreadCallback && cb)
:_tid(0),
_isRunning(false),
_cb(cb)
{

}

Thread::~Thread()
{

}

void Thread::start()
{
    int ret  = pthread_create(&_tid, nullptr,ThreadFunc, this);
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
        int ret = pthread_join(_tid, nullptr);
        if(ret)
        {
            perror("pthread_join");
            return;
        }
        _isRunning = false;
    }

}

void *Thread::ThreadFunc(void *arg)
{
    Thread * pth = static_cast<Thread*>(arg);
    if(pth)
    {
        pth->_cb();
    }
    else
    {
        perror("ThreadFunc");
    }
    pthread_exit(nullptr);
}
