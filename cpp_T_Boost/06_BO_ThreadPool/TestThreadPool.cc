#include "ThreadPool.h"
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask
{
public:
    void process() 
    {
        //做什么任务？
       ::srand(::clock());
       int number = ::rand() %100;
       cout << ">>BO_ThreadPool.MyTask number = " << number << endl;
    }
};

void test()
{
    unique_ptr<MyTask> ptask(new MyTask());
    ThreadPool pool(4, 10);

    pool.start();

    int cnt = 20;
    while(cnt-- > 0)
    {
        pool.addTask(std::bind(&MyTask::process, ptask.get()));
        cout << "cnt = " << cnt << endl;
    }

    pool.stop();
}

int main(int argc, char *argv[])
{
    test();
    return 0;
}

