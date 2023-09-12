#ifndef __PRODUCTOR_H__
#define __PRODUCTOR_H__

#include "Thread.h"

class TaskQueue;

class Productor
:public Thread
{
public:
    Productor(TaskQueue & taskQueue);
    ~Productor();
    void run() override;
private:
    TaskQueue & _taskQueue;
};

#endif
