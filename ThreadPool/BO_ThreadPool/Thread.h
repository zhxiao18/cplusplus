#ifndef _THREAD_H__
#define _THREAD_H__

#include <pthread.h>
#include <iostream>
#include <functional>

using std::function;

using ThreadCallback = function<void()>;
class Thread
{
public:
    Thread(ThreadCallback && cb);
    //虚析构函数
    ~Thread();

    //线程开始、结束
    void start();
    void stop();
private:
    pthread_t _tid;
    bool _isRunning;
    ThreadCallback _cb;
    static void * ThreadFunc(void * arg);
};

#endif
