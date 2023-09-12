#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.h"
#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class Thread;
class Task;

class ThreadPool
{
    friend class WorkThread;//友元
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    //线程池的开始与结束
    void start();
    void stop();
    //添加任务与获取任务
    void  addTask(Task *ptask);
private:
    Task *getTask();

    //线程池交给工作线程做的任务
    void doTask();

private:
    size_t _threadNum;//子线程数目
    vector<unique_ptr<Thread>> _threads;//存放工作线程的容器
    size_t _queSize;//任务队列的大小
    TaskQueue _taskQue;//任务队列
    bool _isExit;//线程池是否退出的标志
};

#endif
