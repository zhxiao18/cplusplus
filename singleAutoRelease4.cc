#include <iostream>
#include <stdlib.h>
#include <pthread.h>

using std::cin;
using std::cout;
using std::endl;

//pthread_once
class Signleton{
public:
    static Signleton * getInstance(){
        pthread_once(&once, init);
        return _pInstence;
    }

    static void init(){
        _pInstence = new Signleton();
        atexit(destroy);
    }
private:
    Signleton(){
        cout << "Signleton()" << endl;
    }

    static void destroy(){
        if(_pInstence){
            delete _pInstence;
            _pInstence = nullptr;
        }
    }

    ~Signleton(){
        cout << "~Signleton()" << endl;
    }
    static Signleton * _pInstence;
    static pthread_once_t once;
};

Signleton * Signleton::_pInstence = getInstance();
pthread_once_t Signleton::once = PTHREAD_ONCE_INIT;

void test01(){
    Signleton * ps1 = Signleton::getInstance(); 
}

int main()
{   
    test01();
    return 0;
}

