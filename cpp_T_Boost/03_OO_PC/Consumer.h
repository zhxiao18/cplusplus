#ifndef __CONSUMER_H__
#define __CONSUMER_H__

#include "Thread.h"

class TaskQueue;//前向声明

class Consumer
: public Thread
{
public:
    Consumer(TaskQueue &taskQue);
    ~Consumer();
    void run() override;
private:
    TaskQueue &_taskQue;
};

#endif
