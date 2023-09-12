#include "Consumer.h"
#include "TaskQueue.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

Consumer::Consumer(TaskQueue &taskQue)
: _taskQue(taskQue)
{

}

Consumer::~Consumer()
{

}

void Consumer::run() 
{
    int cnt = 20;
    while(cnt-- > 0)
    {
        int number = _taskQue.pop();
        cout << ">>Consumer consume = " << number << endl;

        sleep(1);
    }

}
