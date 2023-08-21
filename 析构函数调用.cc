#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class A{
public:
    ~A(){
        cout << "A destroy work." << endl;
    }
};

class B{
public:
    ~B(){
        cout << "B destroy work." << endl;
    }
};

class C{
public:
    ~C(){
        cout << "C destroy work." << endl;
    }
};

class D{
public:
    ~D(){
        cout << "D destroy work." << endl;
    }
};

C c;
int main()
{   
    A *pa = new A();
    B b;
    static D d;
    delete pa;
    return 0;
}

