#include "EventFd.h"
#include "Thread.h"
#include <iostream>
#include <unistd.h>

class MyTask
{
public:
    void process()
    {
        std::cout << "MyTask is running." << std::endl;
    }
};

int main(int argc, char * argv[])
{
    MyTask task;
    EventFd eventfd(std::bind(&MyTask::process, &task));

    Thread th(std::bind(&EventFd::start, &eventfd));
    th.start();

    int cnt = 20;
    while(cnt -- > 0)
    {
        eventfd.wakeup();
        std::cout << "cnt = " << cnt << std::endl;
        sleep(1);
    }

    eventfd.stop();
    th.stop();
}
