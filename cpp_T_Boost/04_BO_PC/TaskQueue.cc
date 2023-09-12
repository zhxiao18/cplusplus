#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex)
{

}

TaskQueue::~TaskQueue()
{

}

//判断任务队列是空还是满
bool TaskQueue::empty() const
{
    return  0 == _que.size() ;
}

bool TaskQueue::full() const
{
    return _que.size() == _queSize;
}

//向任务队列中存数据
void TaskQueue::push(const int &value)
{
    MutexLockGuard autoLock(_mutex);//autoLock是栈对象

    while(full())
    {
        _notFull.wait();
    }

    _que.push(value);

    _notEmpty.notify();
}

//从任务队列中取数据
int TaskQueue::pop()
{
    MutexLockGuard autoLock(_mutex);//autoLock是栈对象

    while(empty())
    {
        _notEmpty.wait();
    }

    int tmp = _que.front();
    _que.pop();

    _notFull.notify();

    return tmp;
}
