#include "Productor.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

void test()
{
    TaskQueue taskQue(10);

    unique_ptr<Thread> pro(new Productor(taskQue));
    unique_ptr<Thread> con(new Consumer(taskQue));

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


