#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

// 内部类 + 静态数据成员
class Signleton
{
public:
    static Signleton *getInstance()
    {
        /* autoRelase ar; */ // error,循环创建
        if (nullptr == _pInstence)
        {
            _pInstence = new Signleton();
            /* autoRelase ar; */ // error，创建完立即就被销毁了，无用
        }
        return _pInstence;
    }

private: // 内部类一般都是作为私有
    class autoRelase
    {
    public:
        autoRelase()
        {
            cout << "autoRelase()" << endl;
        }

        ~autoRelase()
        {
            cout << "~autoRelase()" << endl;
            if (_pInstence)
            {
                delete _pInstence;
                _pInstence = nullptr;
            }
        }
    };

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
    static autoRelase _ar; // 只能作为数据成员
};

Signleton *Signleton::_pInstence = nullptr;
Signleton::autoRelase Signleton::_ar;

void test01()
{
    Signleton *ps1 = Signleton::getInstance();
    /* autoRelase ar;    //私有，访问不到 */
}

int main()
{
    test01();
    return 0;
}
