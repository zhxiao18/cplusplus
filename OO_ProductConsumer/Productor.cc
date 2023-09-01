#include "Productor.h"
#include "TaskQueue.h"
#include <iostream>
#include <unistd.h>

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
    while(num++ < 20){
        _taskQueue.push(num);
        cout << "Productor: " << num << endl;
        sleep(1);
    }
}

