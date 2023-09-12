#include <iostream>
#include <string.h>
#include <cassert>
#include <stdio.h>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

template<class T>
class Singleton{
public:
    template<typename... Args>
    static T *getInstance(Args&&... args)
    {
       pthread_once(&once, init);
       return _pInstance;
    }

    template<typename... Args>
    static void init(Args&&... args){
        if (!_pInstance) {
            _pInstance = new T(std::forward<Args>(args)...);
        }
        atexit(destroy);
    }
private:
    Singleton(){
        cout << "Singleton()" << endl;
    }

    static void destroy(){
        if(_pInstance){
            delete [] _pInstance;
            _pInstance = nullptr;
        }
    }

    ~Singleton(){
        cout << "~Singleton()" << endl;
    }

    static T * _pInstance;
    static pthread_once_t once;
};

template<class T>
T *Singleton<T>::_pInstance = getInstance();

template<class T>
pthread_once_t Singleton<T>::once = PTHREAD_ONCE_INIT;

//- - - - - - - - - - - - - - - - - - - 


class Point{
public:
    Point(){}
    Point(int x, int y){
        _ix = x;
        _iy = y;
        cout << "Point(int,int)" << endl;
    }
    ~Point(){
        cout << "~Point" << endl;
    }
private:
    int _ix;
    int _iy;
};

class Computer{
public:
    Computer(){}

    Computer(string brand, double price)
    :_brand(brand),
    _price(price)
    {
        cout << "Computer(string, double)" << endl;
    }

    void print(){
        cout << _brand << " ->" << _price <<endl;
    }

    ~Computer(){
        cout << "Computer" << endl;
    }
private:
    string _brand;
    double _price;
};

class Point;
class Computer;

Point pt(1, 2);
Point pt2(3, 4);

Computer com("Mac", 8888);

int main()
{   
    Computer *pc1 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    Computer *pc2 = Singleton<Computer>::getInstance("Xiaomi", 6666);
    pc1->print();
    assert(pc1 == pc2);

    Point *pt3 = Singleton<Point>::getInstance(1, 2);
    Point *pt4 = Singleton<Point>::getInstance(1, 2);
    assert(pt3 == pt4);

    return 0;
}

