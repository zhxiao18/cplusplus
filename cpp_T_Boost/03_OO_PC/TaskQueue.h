#ifndef __TASKQUEUE_H__
#define __TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"

#include <queue>
using std::queue;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();

    //任务队列空与满
    bool empty() const;
    bool full() const;

    //存储任务
    void push(const int &value);
    //提取任务
    int pop();

private:
    size_t _queSize;//任务队列的大小
    queue<int> _que;//存放任务的数据结构
    MutexLock _mutex;//创建唯一的一把锁
    Condition _notEmpty;
    Condition _notFull;

};
#endif
