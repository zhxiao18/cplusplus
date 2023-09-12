#include "Producer.h"
#include "Consumer.h"
#include "TaskQueue.h"
#include "Thread.h"
#include <iostream>
#include <memory>
#include <functional>

using std::cout;
using std::endl;
using std::unique_ptr;
using std::bind;

void test()
{
    TaskQueue taskQue(10);
    Producer pr;
    Consumer co;
    //std::ref  std::cref引用的包装器
    unique_ptr<Thread> pro(new Thread(bind(&Producer::run, &pr, std::ref(taskQue))));
    unique_ptr<Thread> con(new Thread(bind(&Consumer::run, &co, std::ref(taskQue))));

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

