#ifndef _WORKTHREAD_H__
#define _WORKTHREAD_H__

#include "Thread.h"
#include "ThreadPool.h"

class WorkThread
:public Thread
{
public:
    WorkThread(ThreadPool & pool) 
    :_pool(pool)
    {

    }

    ~WorkThread() {}

    void run() override
    {
        _pool.doTask();   
    }
private:
    ThreadPool & _pool; 
};

#endif
