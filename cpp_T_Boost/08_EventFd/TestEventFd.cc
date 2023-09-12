#include "EventFd.h"
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
    EventFd efd(std::bind(&MyTask::process, &task)); 
    /* efd.start(); */
    Thread th(std::bind(&EventFd::start, &efd));
    th.start();

    int cnt = 20;
    while(cnt-- > 0)
    {
        efd.wakeup();
        cout << "cnt = " << cnt << endl;
        sleep(1);
    }

    efd.stop();
    th.stop();

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

