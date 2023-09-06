#include "Task.h"
#include "ThreadPool.h"

#include <unistd.h>
#include <memory>

using std::cout;
using std::endl;
using std::unique_ptr;

class MyTask
:public Task
{
public:
    void process () override
    {
        srand(clock());
        int number = rand()%100;
        cout << "number = " << number << endl;
    }
};

void test(){
    unique_ptr<Task> ptask(new MyTask());
    ThreadPool pool(4,10);

    pool.start();

    int cnt = 20;
    while(cnt-- > 0)
    {
        pool.addTask(ptask.get());
        cout << "cnt = " << cnt << endl;
        /* sleep(1); */
    }

    pool.stop();
}

int main()
{   
    test();
    return 0;
}

