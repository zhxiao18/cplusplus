#include "Producer.h"
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

    unique_ptr<Thread> pro(new Producer(taskQue));
    /* unique_ptr<Thread> pro2(new Producer(taskQue)); */
    unique_ptr<Thread> con(new Consumer(taskQue));

    pro->start();
    /* pro2->start(); */
    con->start();

    pro->stop();
    /* pro2->stop(); */
    con->stop();
}

int main(int argc, char *argv[])
{
    test();
    /* MutexLock mtu1; */
    /* MutexLock mtu2 = mtu1;//error */

    /* MutexLock mtu3; */
    /* mtu3 = mtu1;//error */

    /* Thread th1; */
    /* Thread th2 = th1; */

    return 0;
}

