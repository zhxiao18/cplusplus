#include "TaskQueue.h"

TaskQueue::TaskQueue(size_t queSize)
:_queSize(queSize),
_notEmpty(_mutex),
_notFull(_mutex),
_flag(true)
{

}

TaskQueue::~TaskQueue()
{
    
}

//任务入队
void TaskQueue::push(ElemType task)
{
    MutexLockGuard autoLock(_mutex);

    //防止虚假唤醒
    /* if(full()) */
    while(full())
    {
        _notFull.wait();
    }

    _que.push(task);

    _notEmpty.signal();
}

//提取任务
ElemType TaskQueue::pop()
{
    MutexLockGuard autoLock(_mutex);

    while(empty() && _flag)
    {
        _notEmpty.wait();
    }

    if(_flag)
    {

        ElemType tmp = _que.front();
        _que.pop();

        _notFull.signal();
        return tmp;
    }
    else
    {
        return nullptr;
    }
}

bool TaskQueue::full() const
{
    return _queSize == _que.size();
}

bool TaskQueue::empty() const
{
    return 0 == _queSize;
}

void TaskQueue::wakeup()
{
    _flag = false;
    _notEmpty.broadCast();
}
