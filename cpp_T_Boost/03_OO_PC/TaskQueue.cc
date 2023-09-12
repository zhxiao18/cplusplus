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
void TaskQueue::push(const int &value)
{
    //为了防止死锁，可以利用RAII的技术
    //本质：利用栈对象的生命周期管理资源
    //1、先上锁
    /* _mutex.lock(); */
    MutexLockGuard autoLock(_mutex);

    //2、判断是不是满的
    /* if(full()) */
    while(full())//虚假唤醒
    {
        //2.1、如果是满的，就应该睡眠
        _notFull.wait();
    }
    //2.2、如果不满，就可以向queue中存数据
    //存放了数据之后，需要唤醒对方(消费者)
    _que.push(value);

    _notEmpty.notify();

    //3、释放锁
    /* _mutex.unlock(); */
}

//提取任务
int TaskQueue::pop()
{
    //1、先上锁
    /* _mutex.lock(); */
    //锁的粒度(范围)
    int tmp = 0;
    {
        MutexLockGuard autoLock(_mutex);

        //2、判断是不是空的
        /* if(empty()) */
        while(empty())//虚假唤醒
        {
            //2.1、如果为空，就睡眠
            _notEmpty.wait();
        }
        //2.2、如果不空，就pop数据，唤醒对方（生产者）
        tmp = _que.front();
        _que.pop();
        
        _notFull.notify();

    }
    //3、解锁
    /* _mutex.unlock(); */

    return tmp;

}
