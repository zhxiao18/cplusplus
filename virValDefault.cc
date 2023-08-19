#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Base
{
public:
    virtual
        void func(int val = 1){
            cout << "Base -> " << val << endl;
        }

    virtual 
        void test(){
            func();
        }
private:
    long _base;
};

class Derived
: public Base
{
public:
    void func(int val = 10){
        cout << "Derived -> " << val << endl;
    }
private:
    long _derived;
};

void test01(){
    Derived derived;
    Base * pbase = &derived;
    Derived *pderived = &derived;
    pbase->func(); //Derived -> 1
    pderived->func(); //Derived -> 10
}

int main()
{   
    test01();
    return 0;
}

