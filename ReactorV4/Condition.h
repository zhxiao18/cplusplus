#ifndef _CONDITION_H__
#define _CONDITION_H__

#include <pthread.h>

class MutexLock;//前向声明

class Condition
{
public:
    Condition(MutexLock & mutex);
    ~Condition();
    //等待
    void wait();
    //唤醒
    void signal();
    void broadCast();
private:
    pthread_cond_t _cond;
    MutexLock & _mutex;
};

#endif
