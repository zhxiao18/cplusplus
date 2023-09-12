#ifndef _CONDITION_H__
#define _CONDITION_H__

#include "NoCopyable.h"
#include <pthread.h>

class MutexLock;

class Condition
:public NoCopyable  //禁止复制
{
public:
    Condition(MutexLock & mutex);
    ~Condition();
    void wait();
    void signal();
    void broadcast();
private:
    pthread_cond_t _cond;
    MutexLock & _mutex;
};

#endif
