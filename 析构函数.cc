#include <iostream>
#include<string.h>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;

class Computer{
public:
    Computer(const char * brand, double price)
    :_price(price),
    _brand(new char[strlen(brand) + 1]())
    {
        cout << "Computer的构造函数被调用了。" << endl;
        strcpy(_brand, brand);
    }

    void print(){
        cout << "_brand: " << _brand << endl
            << "_price: " << _price << endl;
    }
        
    ~Computer(){
        cout << "~Computer" << endl;
        if(_brand){
            delete [] _brand;
            _brand = nullptr;
            cout << "delete" << endl;
        }
    }
private:
    char * _brand;
    double _price;
};

void test(){
    Computer cmp("华为", 1999);
    cmp.print();
}

int main()
{
    test();

    return 0;
}

