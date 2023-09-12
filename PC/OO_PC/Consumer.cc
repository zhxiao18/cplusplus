#include "Consumer.h"
#include "TaskQueue.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

Consumer::Consumer(TaskQueue & taskQue)
:_taskQueue(taskQue)
{
    
}

Consumer::~Consumer(){

}

void Consumer::run(){
    int num = 20;
    while(num-- > 0)
    {
        int val = _taskQueue.pop();
        cout << "comsumer: " << val << endl;

        sleep(1);
    }
}
