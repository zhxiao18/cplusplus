#include <iostream>
#include <string.h>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;

// 友元的形式
class Signleton
{
public:
    static Signleton *getInstance()
    {
        if (nullptr == _pInstence)
        {
            atexit(destroy);
            _pInstence = new Signleton();
        }
        return _pInstence;
    }

    static void destroy()
    {
        if (Signleton::_pInstence)
        {
            delete Signleton::_pInstence;
            Signleton::_pInstence = nullptr;
        }
    }

private:
    Signleton()
    {
        cout << "Signleton()" << endl;
    }

    ~Signleton()
    {
        cout << "~Signleton()" << endl;
    }
    static Signleton *_pInstence;
};

// 无法应对多线程的需求
/* Signleton * Signleton::_pInstence = nullptr; */

// 不太优雅
Signleton *Signleton::_pInstence = Signleton::getInstance();

void test01()
{
    Signleton *ps1 = Signleton::getInstance();
}

int main()
{
    test01();
    return 0;
}
