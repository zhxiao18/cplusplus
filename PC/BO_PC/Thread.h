#ifndef __THREAD_H__
#define __THREAD_H__

#include <functional>
#include <pthread.h>

using std::function;

class Thread
{
    using ThreadCallback = function<void()>;
public:
    Thread(ThreadCallback && cb);
    ~Thread();
    void start();
    void stop();
private:
    //线程入口函数
    static void * ThreadFunc(void * arg);
private:
    pthread_t _tid;
    bool _isRunning;
    ThreadCallback _cb;
};

#endif

