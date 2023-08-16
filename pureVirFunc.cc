#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Base{
public:
    virtual void display() = 0;
};

class Derived1
:public Base
{
    
};

class Derived2
:public Base
{
public:
    void display() override{
        cout << "Derived2::display" << endl;
    }
};

class A;

void test01(){
    /* Base base; //error,variable type 'Base' is an abstract class */

    /* Derived1 derived1; //error,没有重写纯虚函数 */

    Derived2 derived2;
    derived2.display(); //Derived2::display  

    Base * pbase = &derived2; //抽象类不可以创建对象，可以创建指针
    pbase->display(); //Derived2::display 

    /* A a; //error,variable has incomplete type 'A' */
    A *pa; //可以创建不完整类型的指针
}

int main()
{   
    test01();
    return 0;
}

