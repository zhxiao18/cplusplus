#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "Noncopyable.h"
#include <pthread.h>

class MutexLock;//前向声明

class Condition
: Noncopyable
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
    MutexLock &_mutex;//互斥锁的引用
    pthread_cond_t _cond;//条件变量

};

#endif
