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
    /* virtual void print(){ */
    /*     cout << "Derived::print" << endl; */
    /* } */
};


int main()
{   
    Base *base;
    Derived derived;
    
    //基类指针指向派生类对象
    base = &derived;

    base->print();
    base->display();

    cout << sizeof(Base) << endl;
    cout << sizeof(Derived) << endl;
    return 0;
}

