#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

class Thread
{
public:
    Thread();
    ~Thread();
    void start();
    void stop();
private:
    //线程入口函数
    static void * ThreadFunc(void * arg);
    //具体的线程任务，设置成纯虚函数，由子类实现
    virtual void run() = 0;
private:
    pthread_t _tid;
    bool _isRunning;
};

#endif

