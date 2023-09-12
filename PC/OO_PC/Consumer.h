#ifndef _CONSUMER_H__
#define _CONSUMER_H__

#include "Thread.h"

class TaskQueue;

class Consumer
:public Thread
{
public:
    Consumer(TaskQueue & taskQue);
    ~Consumer();
    void run() override;
private:
    TaskQueue & _taskQueue;
};

#endif
