#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Base{
public:
    virtual void display(){
        cout << "Base::display" << endl;
    }

    //使用普通成员函数进行调用虚函数
    void func(){
        this->display();//可以体现多态
    }

    void func2(){
        Base::display();
    }
};

class Derived
:public Base
{
public:
    void display(){
        cout << "Derived::display" << endl;
    }
};

int main()
{   
    Base *pbase, base;
    Derived derived;

    pbase = &base;
    pbase->func();

    pbase = &derived;
    pbase->func();

    return 0;
}

