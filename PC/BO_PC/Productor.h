#ifndef __PRODUCTOR_H__
#define __PRODUCTOR_H__

class TaskQueue;

class Productor
{
public:
    Productor();
    ~Productor();
    void run(TaskQueue & taskQue);
};

#endif
