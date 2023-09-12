#ifndef __CONSUMER_H__
#define __CONSUMER_H__


class TaskQueue;//前向声明

class Consumer
{
public:
    Consumer();
    ~Consumer();

    void run(TaskQueue &taskQue) ;

private:
};

#endif
