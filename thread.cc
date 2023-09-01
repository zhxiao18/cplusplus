//面向对象封装线程
#include <iostream>
#include <pthread.h>
#include <unistd.h>

using std::cout;
using std::endl;

class Thread
{
public:
    Thread();
    virtual ~Thread();
    void start();
    void stop();
private:
    //必须是静态的，要消除this指针的影响
    static void * ThreadFunc(void * arg);
    virtual void run() = 0;
private:
    pthread_t _tid;
    bool _isRunning;
};

Thread::Thread()
:_tid(0),
_isRunning(false)
{

}

Thread::~Thread()
{

}

void Thread::start(){
    int ret = pthread_create(&_tid,nullptr,ThreadFunc,this);
    if(ret){
        perror("pthread_create");
        return;
    }
    _isRunning = true;
}

void Thread::stop(){
    if(_isRunning){
        int ret = pthread_join(_tid, nullptr);
        if(ret){
            perror("pthread_join");
            return;
        }
        _isRunning = false;
    }
}

void * Thread::ThreadFunc(void * arg){
    Thread * pth = static_cast<Thread *>(arg);
    if(pth){
        pth->run();
    }else{
        cout << "pth == nullptr" << endl;
    }
    pthread_exit(nullptr);
}

class MyThread
:public Thread
{
private:
    void run() override {
        while(1){
            cout << "MyThread is running." << endl;
            sleep(1);
        }
    }
};

void test01(){
    Thread * pth = new MyThread();
    pth->start();
    pth->stop();
}

int main()
{   
    test01();
    return 0;
}

