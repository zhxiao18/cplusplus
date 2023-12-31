#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "NonCopyable.h"
#include <pthread.h>

class MutexLock;//前向声明

class Condition
: NonCopyable
{
public:
    Condition(MutexLock &mutex);
    ~Condition();

    //等待函数
    void wait();
    //通知函数
    void notify();
    void notifyAll();

private:
    pthread_cond_t _cond;
    MutexLock &_mutex;

};

#endif
