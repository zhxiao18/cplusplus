#include "Productor.h"
#include "TaskQueue.h"
#include <iostream>
#include <unistd.h>
#include <time.h>

using std::cout;
using std::endl;

Productor::Productor()
{

}

Productor::~Productor(){

}

void Productor::run(TaskQueue & taskQue){
    int num = 0;
    ::srand(time(nullptr));
    while(num++ < 20){
        int number = ::rand()%100;
        taskQue.push(number);
        cout << "Productor: " << num << endl;
        sleep(1);
    }
}

