#include "TimerFd.h"
#include "Thread.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

class MyTask
{
public:
    void process()
    {
        cout << "MyTask is running!!!" << endl;
    }
};

void test()
{
    MyTask task;
    TimerFd tfd(1, 6, std::bind(&MyTask::process, &task)); 
    Thread th(std::bind(&TimerFd::start, &tfd));
    th.start();

    sleep(30);

    tfd.stop();
    th.stop();

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

