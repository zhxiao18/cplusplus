#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Computer{
public:
    Computer(const char * brand, double price)
    :_brand(new char[strlen(brand) + 1]())
    ,_price(price)
    {
        strcpy(_brand, brand);
        cout << "Computer(const char * brand, double price)" << endl;
    }

    //默认拷贝构造:浅拷贝
    /* Computer(const Computer & rhs) */
    /* :_brand(rhs._brand) */
    /* ,_price(rhs._price) */
    /* { */
    /*     cout << "Computer(const Computer & rhs)" << endl; */
    /* } */

    Computer(const Computer & rhs)
    :_brand(new char[strlen(rhs._brand) + 1]()),
    _price(rhs._price)
    {
        strcpy(_brand, rhs._brand);
        cout << "Computer(const Computer & rhs)" << endl;
    }

    void print(){
        cout << "brand: " << _brand << endl
            << "price: " << _price << endl;
    }

    ~Computer(){
        delete []  _brand;
        _brand = nullptr;
        cout << "~Computer()" << endl;
    }
private:
    char * _brand;
    double _price;
};

void func(Computer cmp){
    cmp.print();
}

//3.拷贝构造时机3：return 类类型
Computer func2(){
    Computer cmp3("huawei", 1999);
    cout << "cmp3: " << endl;
    cmp3.print();
    return cmp3;

}

void test01(){
    Computer cmp1("xiaomi", 1000);
    cmp1.print();

    //1.用一个已经存在的对象初始化一个新创建的对象
    Computer cmp2 = cmp1;
    cmp2.print();

    //2.形参与实参结合
    func(cmp2);

    func2();
}

int main()
{   
    test01();
    return 0;
}

