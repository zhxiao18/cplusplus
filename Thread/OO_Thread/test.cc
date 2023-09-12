#include "Thread.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

class myThread
:public Thread
{
private:
    void run() override
    {
        while(1)
        {
            cout << "myThread is running" << endl;
            sleep(1);
        }
    }
};

void test()
{
    myThread thread;
    thread.start();

    thread.stop();
}

int main(void)
{
    test();
    return 0;
}
