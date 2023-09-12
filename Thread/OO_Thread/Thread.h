#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>

class Thread
{
public:
    Thread();
    //虚析构
    virtual ~Thread();

    //线程开始、结束
    void start();
    void stop();

private:
    static void * ThreadFunc(void * arg);

    //纯虚函数，子线程实现
    virtual void run() = 0;
private:
    pthread_t _thid;

    //标识线程是否运行
    bool _isRunning;
};

#endif


