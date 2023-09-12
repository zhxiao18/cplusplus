#include "Thread.h"
#include <stdio.h>

using std::cout;
using std::endl;

Thread::Thread(ThreadCallback && cb)
:_tid(0),
_isRunning(false),
_cb(std::move(cb))
{

}

//虚析构函数
Thread::~Thread()
{

}

//线程开始、结束
void Thread::start()
{
    int ret = pthread_create(&_tid, nullptr, ThreadFunc, this);
    if(ret)
    {
        perror("pthread_create");
        return;
    }
    _isRunning = true;;
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

void * Thread::ThreadFunc(void * arg)
{
    Thread * pth = static_cast<Thread *>(arg);
    if(pth)//如果不是空指针
    {
        pth->_cb();
    }
    else
    {
        cout << "pth == nullptr" << endl;
    }

    pthread_exit(nullptr);
}
