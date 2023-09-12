#include "Producer.h"
#include "TaskQueue.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

Producer::Producer(TaskQueue &taskQue)
: _taskQue(taskQue)
{

}

Producer::~Producer()
{

}

void Producer::run() 
{
    //生产int类型的数据
    ::srand(::clock());

    int cnt = 20;
    while(cnt-- > 0)
    {
        int number = ::rand() % 100;
        _taskQue.push(number);
        cout << ">>Producer produce = " << number << endl;

        sleep(1);
    }

}
