#ifndef __MUTEXLOCK_H__
#define __MUTEXLOCK_H__

#include "Noncopyable.h"
#include <pthread.h>

class MutexLock
: Noncopyable
{
public:
    MutexLock();
    ~MutexLock();

    //上锁与解锁的函数
    void lock();
    void tryLock();
    void unLock();

    pthread_mutex_t *getMutexLockPtr();

private:
    pthread_mutex_t _mutex;

};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock &mutex)
    : _mutex(mutex)
    {
        _mutex.lock();
    }

    ~MutexLockGuard()
    {
        _mutex.unLock();
    }
private:
    MutexLock &_mutex;
};
#endif
