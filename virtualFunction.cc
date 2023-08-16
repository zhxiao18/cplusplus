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
    virtual void print(){
        cout << "Base::print" << endl;
    }
};

class Derived
:public Base{
public:
    virtual void display(){
        cout << "Derived::display" << endl;
    }
    virtual void print(){
        cout << "Derived::print" << endl;
    }
};

void test01(Base * pbase){
    pbase->display();
}

int main()
{   
    Base base;
    Derived derived;
    test01(&base); //*pbase = &bease;
    test01(&derived);// Base *pbase = &derived;
    return 0;
}

