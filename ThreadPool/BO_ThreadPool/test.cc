#include "ThreadPool.h"
#include <unistd.h>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask
{
public:
    void process ()
    {
        srand(clock());
        int number = rand()%100;
        cout << "BO_ThreadPool::number = " << number << endl;
    }
};

void test(){
    unique_ptr<MyTask> ptask(new MyTask());
    ThreadPool pool(4,10);

    pool.start();

    int cnt = 20;
    while(cnt--)
    {
        pool.addTask((std::bind(&MyTask::process, ptask.get())));
        cout << "cnt = " << cnt << endl;
        sleep(1);
    }

    pool.stop();
}

int main()
{   
    test();
    return 0;
}
