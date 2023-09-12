#include "Productor.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include "Thread.h"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

void test()
{
    TaskQueue taskQue(10);
    Productor pr;
    Consumer co;

    unique_ptr<Thread> pro(new Thread(std::bind(&Productor::run, &pr, std::ref(taskQue))));
    unique_ptr<Thread> con(new Thread(std::bind(&Consumer::run, &co, std::ref(taskQue))));

    pro->start();
    con->start();

    pro->stop();
    con->stop();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


