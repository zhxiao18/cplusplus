#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>

using std::function;

class Thread
{
    using ThreadCallback = function<void()>;
public:
    Thread(ThreadCallback &&cb);
    ~Thread();

    //线程开始与结束
    void start();
    void stop();

private:
    //线程入口函数
    static void *threadFunc(/* * this */void *arg);

private:
    pthread_t _thid;//线程id
    bool _isRunning;//标识线程是否在运行
    ThreadCallback _cb;//线程执行的任务
};

#endif
