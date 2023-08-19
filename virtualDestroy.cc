#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Base{
public:
    Base(const char * str)
    :_pbase(new char[strlen(str) + 1]())
    {
        cout << "Base(const char * str)" << endl;
        strcpy(_pbase, str);
    }

    virtual
    void print(){
        cout << "_pbase: " << _pbase << endl; 
    }

    virtual
    ~Base(){
        if(_pbase){
            delete [] _pbase;
            _pbase = nullptr;
        }
        cout << "~Base()" << endl;
    }
private:
    char * _pbase;
};

class Derived
:public Base
{
public:
    Derived(const char * pbase, const char * pderived)
        :Base(pbase),
        _pderived(new char[strlen(pderived) + 1]())
    {
        cout << "Derived(const char * pbase, const char * pderived)" << endl;
        strcpy(_pderived, pderived);
    }

    void print(){
        cout << "_pderived: " <<  _pderived << endl;
    }

    ~Derived(){
        if(_pderived){
            delete [] _pderived;
            _pderived = nullptr;
        }
        cout << "~Derived" << endl;
    }
private:
    char * _pderived;
};

void test01(){
    Base *pbase= new Derived("hello", "world");
    pbase->print();
    
    delete pbase;
    pbase = nullptr;
}

int main()
{   
    test01();
    return 0;
}

