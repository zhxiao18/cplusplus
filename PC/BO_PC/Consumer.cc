#include "Consumer.h"
#include "TaskQueue.h"
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

Consumer::Consumer()
{
    
}

Consumer::~Consumer(){

}

void Consumer::run(TaskQueue & taskQue){
    int num = 20;
    while(num-- > 0)
    {
        int val = taskQue.pop();
        cout << "comsumer: " << val << endl;

        sleep(1);
    }
}
