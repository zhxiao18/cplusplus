#include <iostream>
using namespace std;

// 单例模式：一个类只有一个对象
class Signleton
{
public:
    static Signleton *getInstance()
    {
        if (nullptr == _pInstance)
        {
            _pInstance = new Signleton(); // 类内创建对象
        }
        return _pInstance;
    }

    static void destroy()
    {
        if (_pInstance)
        {
            delete _pInstance;
            _pInstance = nullptr;
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

private:
    static Signleton *_pInstance;
};

Signleton *Signleton::_pInstance = nullptr;

void test01()
{
    Signleton *sigl1 = Signleton::getInstance();
    Signleton *sigl2 = Signleton::getInstance();
    cout << "sigl1: " << sigl1 << endl;
    cout << "sigl2: " << sigl2 << endl;
    Signleton::destroy();
}

int main()
{
    test01();
    return 0;
}