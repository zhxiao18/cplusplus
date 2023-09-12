#include "Productor.h"
#include "TaskQueue.h"
#include <iostream>
#include <unistd.h>
#include <time.h>

using std::cout;
using std::endl;

Productor::Productor(TaskQueue & taskQueue)
:_taskQueue(taskQueue)
{

}

Productor::~Productor(){

}

void Productor::run(){
    int num = 0;
    srand(time(nullptr));
    while(num++ < 20){
        int number = ::rand()%100;
        _taskQueue.push(number);
        cout << "Productor: " << num << endl;
        sleep(1);
    }
}

