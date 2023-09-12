#include "Thread.h"
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

void func()
{
    while(1)
    {
        cout << "thread is running." << endl;
        sleep(1);
    }
}

void test()
{
    Thread thread(std::move(func));
    thread.start();

    thread.stop();
}

int main(void)
{
    test();
    return 0;
}
