#ifndef _TASKQUEUE_H__
#define _TASKQUEUE_H__

#include "Condition.h"
#include "MutexLock.h"
#include <iostream>
#include <queue>

using std::queue;

class Task;

using ElemType = Task *;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    //任务入队
    void push(ElemType task);
    //提取任务
    ElemType pop();

    bool full() const;
    bool empty() const;

    void wakeup();
private:
    size_t _queSize;
    queue<ElemType> _que;//存放任务
    MutexLock _mutex;
    Condition _notEmpty;
    Condition _notFull;
    bool _flag; //唤醒线程之后能够退出循环
};

#endif
