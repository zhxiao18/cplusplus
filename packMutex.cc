#include <iostream>
#include <pthread.h>

using std::cin;
using std::cout;
using std::endl;

class MutexLock
{
public:
    MutexLock(){
        cout << "MutexLock()" << endl;
    }

    void lock(){
        int ret = pthread_mutex_init(&_mutex,nullptr);
        if(ret){
            cout << "pthread_mutex_init" << endl;
            return;
        }

        pthread_mutex_lock(&_mutex);
    }

    void unlock(){
        pthread_mutex_unlock(&_mutex);
    }

    void trylock(){
        pthread_mutex_trylock(&_mutex);
    }
private:
    pthread_mutex_t _mutex;
};

void test01(){

}

int main()
{   
    test01();
    return 0;
}

