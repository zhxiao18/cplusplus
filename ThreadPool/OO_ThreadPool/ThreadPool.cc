#include "ThreadPool.h"
#include "WorkThread.h"
#include "Task.h"

#include <unistd.h>

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
:_threadNum(threadNum),
_queSize(queSize),
_taskQue(_queSize),
_isExit(false)
{
    //预留空间
    _threads.reserve(_threadNum);    
}

ThreadPool::~ThreadPool()
{
        
}

void ThreadPool::start()
{
   for(size_t idx = 0; idx < _threadNum; ++idx)
   {
       //创建子线程
       unique_ptr<Thread> up(new WorkThread(*this));
       //unique_ptr需要传递右值
       _threads.push_back(std::move(up));
   }

   for(auto &th : _threads)
   {
        th->start();
   }
}

void ThreadPool::stop()
{
    //要确保所有任务执行完毕，再关闭线程
    while(!_taskQue.empty())
    {
        //sleep的时候会交出CPU控制权
        sleep(1);
    }

    _isExit = true;

    _taskQue.wakeup();

    for(auto &th : _threads)
    {
        th->stop();
    }
}

void ThreadPool::addTask(Task * task)
{
    if(task)
    {
        _taskQue.push(task);
    }
}

Task * ThreadPool::getTask()
{
    return _taskQue.pop();
}

void ThreadPool::doTask()
{
    while(!_isExit)
    {
        Task * ptask = getTask();
        if(ptask)
        {
            ptask->process();
        }
    }
}
