#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
: _queSize(queSize)
, _que()
, _mutex()
, _notEmpty(_mutex)
, _notFull(_mutex)
, _flag(true)
{

}

TaskQueue::~TaskQueue()
{

}

//任务队列空与满
bool TaskQueue::empty() const
{
    return 0 == _que.size();
}

bool TaskQueue::full() const
{
    return _queSize == _que.size();
}


//存储任务
void TaskQueue::push(ElemType value)
{
    MutexLockGuard autoLock(_mutex);

    while(full())//虚假唤醒
    {
        _notFull.wait();
    }

    _que.push(value);

    _notEmpty.notify();
}

//提取任务
ElemType TaskQueue::pop()
{
    MutexLockGuard autoLock(_mutex);

    while(empty() && _flag)//虚假唤醒
    {
        _notEmpty.wait();
    }

    if(_flag)
    {
        ElemType tmp = _que.front();
        _que.pop();
        
        _notFull.notify();

        return tmp;
    }
    else
    {
        return nullptr;
    }
}

void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.notifyAll();
}
