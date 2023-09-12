#ifndef __THREAD_H__
#define __THREAD_H__

#include "NonCopyable.h"
#include <pthread.h>

class Thread
: NonCopyable
{
public:
    Thread();
    virtual ~Thread();

    //线程开始与结束
    void start();
    void stop();

private:
    //线程入口函数
    static void *threadFunc(/* * this */void *arg);
    //线程需要执行的任务
    virtual void run() = 0;

private:
    pthread_t _thid;//线程id
    bool _isRunning;//标识线程是否在运行

};

#endif
