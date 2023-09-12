#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include "NonCopyable.h"
#include <pthread.h>

class MutexLock
: NonCopyable
{
public:
    MutexLock();
    ~MutexLock();

    //上锁
    void lock();
    //尝试上锁
    void tryLock();
    //解锁
    void unlock();

    pthread_mutex_t *getMutexLockPtr()
    {
        return &_mutex;
    }

private:
    pthread_mutex_t _mutex;

};

class MutexLockGuard
{
public:
    //在构造函数中上锁
    MutexLockGuard(MutexLock &mutex)
    : _mutex(mutex)
    {
        _mutex.lock();
    }

    //在析构函数中进行解锁
    ~MutexLockGuard()
    {
        _mutex.unlock();
    }
private:
    MutexLock &_mutex;
};

#endif

