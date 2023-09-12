#include "Producer.h"
#include "TaskQueue.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

Producer::Producer()
{

}

Producer::~Producer()
{

}

void Producer::run(TaskQueue &taskQue) 
{
    ::srand(::clock());
    int cnt = 20;
    while(cnt--)
    {
        int number = rand()%100;
        taskQue.push(number);
        cout << ">>Producer produce = " << number << endl;
        sleep(1);
    }
}
