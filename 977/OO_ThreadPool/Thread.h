#ifndef _THREAD_H__
#define _THREAD_H__

#include <pthread.h>
#include <iostream>

class Thread
{
public:
    Thread();
    //虚析构函数
    virtual ~Thread();

    //线程开始、结束
    void start();
    void stop();
private:
    pthread_t _tid;
    bool _isRunning;

    static void * ThreadFunc(void * arg);

    //线程具体任务
    virtual void run() = 0;
};

#endif
