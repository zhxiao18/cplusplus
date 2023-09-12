#ifndef _TASKQUEUE_H__
#define _TASKQUEUE_H__

#include "MutexLock.h"
#include "Condition.h"
#include <queue>

using std::queue;

class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    ~TaskQueue();
    //存入任务
    void push(const int & value);
    //提取任务
    int pop();
    bool empty();
    bool full();
private:
    size_t _queSize;
    queue<int> _que;
    MutexLock  _mutex;
    Condition _notifyEmpty;
    Condition _notifyFull;
};

#endif
