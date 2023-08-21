#include <iostream>
#include<string.h>

using std::cin;
using std::cout;
using std::endl;

class Animal{
public:
    Animal(){
        cout << "Animal 的无参构造被调用了。" << endl;
    }

    Animal(const char* family, int age, const char* color)
    :_family(family),
    _age(age),
    _color(color)
    {
        cout << "Animal的有参构造函数被调用了。" << endl;
    }

    void print(){
        cout << "family:" << _family << endl;
        cout << "age:" << _age << endl;
        cout << "color:" << _color << endl;
    }
private:
    const char * _family;
    int _age;
    const char * _color;
};

int main()
{
    Animal animal1;
    Animal animal2("猫科", 2, "black");
    /* animal1.print(); */      //段错误 (核心已转储)
    animal2.print();
    return 0;
}

