#ifndef _THREADPOOL_H__
#define _THREADPOOL_H__

#include "TaskQueue.h"
#include <pthread.h>
#include <vector>
#include <memory>

class Task;
class Thread;

using std::vector;
using std::unique_ptr;

class ThreadPool
{
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();
    void start();
    void stop();
    void addTask(Task * task);
    Task * getTask();
    void doTask();
private:
    size_t _threadNum;    //子线程个数
    vector<unique_ptr<Thread>> _threads; //子线程容器
    size_t _queSize;    //队列长度
    TaskQueue _taskQue;
    bool _isExit;    //线程池是否退出
};

#endif
