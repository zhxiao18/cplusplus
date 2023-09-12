#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"

#include <queue>
using std::queue;

class Task;//前向声明

using ElemType = Task *;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    //任务队列空与满
    bool empty() const;
    bool full() const;

    //存储任务
    void push(ElemType value);
    //提取任务
    ElemType pop();
    //唤醒所有等待在_notEmpty条件变量上的线程
    void wakeup();

private:
    size_t _queSize;//任务队列的大小
    queue<ElemType> _que;//存放任务的数据结构
    MutexLock _mutex;//创建唯一的一把锁
    Condition _notEmpty;
    Condition _notFull;
    bool _flag;//标识作用

};
#endif
