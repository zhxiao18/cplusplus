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

    Computer(const Computer & rhs)
    :_brand(new char[strlen(rhs._brand) + 1]()),
    _price(rhs._price)
    {
        strcpy(_brand, rhs._brand);
        cout << "Computer(const Computer & rhs)" << endl;
    }

    Computer &operator=(const Computer & rhs){
        cout << "Computer &operator=(const Computer & rhs)" << endl;
        
        if(this != &rhs){
            delete [] _brand;
            _brand = nullptr;

            _brand = new char[strlen(rhs._brand) + 1]();
            strcpy(_brand, rhs._brand);
            _price = rhs._price;
        }

        return *this;
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

void test01(){
    Computer cmp1("xiaomi", 1000);
    cmp1.print();

    Computer cmp2 = cmp1;
    cmp2.print();

    Computer cmp3("huawei",2999.7);

    cmp2 = cmp3;
    cmp2.print();
    cmp3.print();
}

int main()
{   
    test01();
    return 0;
}

