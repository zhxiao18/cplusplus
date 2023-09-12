#ifndef _CONSUMER_H__
#define _CONSUMER_H__

class TaskQueue;

class Consumer
{
public:
    Consumer();
    ~Consumer();
    void run(TaskQueue & taskQue);
};

#endif
