#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

//友元的形式
class Signleton{
    friend class autoRelase;
public:
    static Signleton * getInstance(){
        if(nullptr == _pInstence){
            _pInstence = new Signleton();
        }
        return _pInstence;
    }
private:
    Signleton(){
        cout << "Signleton()" << endl;
    }

    ~Signleton(){
        cout << "~Signleton()" << endl;
    }
static Signleton * _pInstence;
};

class autoRelase{
public:
    autoRelase(){
        cout << "autoRelase()" << endl;
    }

    ~autoRelase(){
        cout << "~autoRelase()" << endl;
        if(Signleton::_pInstence){
            delete Signleton::_pInstence;
            Signleton::_pInstence = nullptr;
        }
    }
};

Signleton * Signleton::_pInstence = nullptr;

void test01(){
    Signleton * ps1 = Signleton::getInstance(); 
    autoRelase ar;
}

int main()
{   
    test01();
    return 0;
}

