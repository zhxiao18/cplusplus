#include "TaskQueue.h"
    
TaskQueue::TaskQueue(size_t queSize)
:_queSize(queSize),
_notifyEmpty(_mutex),
_notifyFull(_mutex)
{

}

TaskQueue::~TaskQueue(){

}

//存入任务
void TaskQueue::push(const int & value){
    //RAII，利用栈对象的生命周期管理锁
    MutexLockGuard autoMutex(_mutex); 

    //使用while，防止虚假唤醒
    while(full()){
        _notifyFull.wait();
    }

    _que.push(value);

    _notifyEmpty.signal();
}

//提取任务
int TaskQueue::pop(){
    int tmp = 0;
    {
        MutexLockGuard autoMutex(_mutex);

        while(empty()){
            _notifyEmpty.wait();
        }

        tmp = _que.front();
        _que.pop();

        _notifyFull.signal();
    }
    return tmp;
}

bool TaskQueue::empty(){
    return 0 == _que.size();
}

bool TaskQueue::full(){
    return _queSize == _que.size();
}
