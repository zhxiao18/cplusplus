#ifndef __THREAD_H__
#define __THREAD_H__

#include <pthread.h>
#include <functional>

using std::function;

using ThreadCallback = function<void()>;

class Thread
{
public:
    Thread(ThreadCallback && cb);
    //虚析构
    ~Thread();

    //线程开始、结束
    void start();
    void stop();

private:
    static void * ThreadFunc(void * arg);
private:
    pthread_t _thid;

    //标识线程是否运行
    bool _isRunning;

    ThreadCallback _cb;
};

#endif


