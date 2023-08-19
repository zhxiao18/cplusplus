#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

//抽象类的第二种形式：将构造函数声明成protect
class Base{
protected:
    Base(){
        cout << "Base()" << endl;
    }
};

class Derived
: public Base
{
public:
    Derived()
    :Base()
    {
        cout << "Derived()" << endl;
    }
};

void test01(){
    Derived derived;
    /* Base base; */ //error
}

int main()
{   
    test01();
    return 0;
}

