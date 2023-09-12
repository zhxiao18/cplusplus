#include "ThreadPool.h"
#include "WorkThread.h"
#include "Task.h"
#include <unistd.h>

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
: _threadNum(threadNum)
, _queSize(queSize)
, _taskQue(_queSize)
, _isExit(false)
{
    //为了防止扩容，可以预留空间
    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool()
{

}

//线程池的开始与结束
void ThreadPool::start()
{
    for(size_t idx = 0; idx < _threadNum; ++idx)
    {
        unique_ptr<Thread> up(new WorkThread(*this));//创建的子线程
        _threads.push_back(std::move(up));//unique_ptr作为容器元素需要传递右值
    }

    for(auto &th : _threads)
    {
        //将所有的工作线程都运行起来
        th->start();
    }
}

void ThreadPool::stop()
{
    //任务只要不执行完毕，程序就不能退出，也就是线程池不能退出
    while(!_taskQue.empty())
    {
        sleep(1);
    }

    _isExit = true;

    //唤醒所有在_notEmpty条件变量上的线程，也就是工作线程
    _taskQue.wakeup();

    for(auto &th : _threads)
    {
        //将所有的工作线程都停止运行
        th->stop();
    }
}

//添加任务与获取任务
void  ThreadPool::addTask(Task *ptask)
{
    if(ptask)
    {
        _taskQue.push(ptask);
    }
}

Task *ThreadPool::getTask()
{
    return _taskQue.pop();
}

//线程池交给工作线程做的任务
void ThreadPool::doTask()
{
    //要保证只要线程池里面有任务，也就是TaskQueue中有任务，那么线程池中的工作线程就应该一直需要处理任务
    while(!_isExit)
    {
        //子线程获取到任务之后，需要进行执行process函数，那么如果process执行的速率比较慢的话，那么主线程就有足够的时间将标志位_isExit设置为true，那么当工作线程执行完process之后，再走while循环的时候，发现不满足条件就不会再进入while,那么就不会再走getTask，也就不会阻塞;如果工作线程执行process的速率非常快的话，那么可能出现主线程还没有来得及将标志位设置为_isExit的时候，工作线程又进入了while循环，但是此时任务队列中没有任务，所以调用getTask工作线程就会阻塞
        Task *ptask = getTask();
        if(ptask)
        {
            //执行任务
            ptask->process();//多态
        }
    }
}
