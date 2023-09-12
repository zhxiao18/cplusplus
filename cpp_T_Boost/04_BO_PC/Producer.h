#ifndef __PRODUCER_H__
#define __PRODUCER_H__

class TaskQueue;//前向声明

class Producer
{
public:
    Producer();
    ~Producer();

    void run(TaskQueue &taskQue);

private:
};

#endif
