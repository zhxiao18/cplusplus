#ifndef _MUTEXLOCK_H__
#define _MUTEXLOCK_H__

#include <pthread.h>

class MutexLock
{
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();
    void trylock();
    pthread_mutex_t * getMutexLockPtr();
private:
    pthread_mutex_t _mutex;
};

//RAII,防止死锁
class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock & mutex)
    :_mutex(mutex)
    {
        _mutex.lock();
    }

    ~MutexLockGuard()
    {
        _mutex.unlock();
    }
private:
    MutexLock & _mutex;
};

#endif
