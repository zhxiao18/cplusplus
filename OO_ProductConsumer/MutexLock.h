#ifndef _MUTEXLOCK_H__
#define _MUTEXLOCK_H__
#include "NoCopyable.h"
#include <pthread.h>

class MutexLock
:public NoCopyable
{
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();
    void trylock();

    pthread_mutex_t * getMutexLockPtr(){
        return &_mutex;
    }

private:
    pthread_mutex_t _mutex;
};

//TaskQueue中使用到
//利用RAII思想
//为了防止死锁，在构造函数中上锁，在析构函数中解锁
class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock & mutex)
    :_mutex(mutex){ 
        _mutex.lock();
    }

    ~MutexLockGuard(){
        _mutex.unlock();
    }
private:
        MutexLock & _mutex;
};

#endif
