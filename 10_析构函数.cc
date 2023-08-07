#include <iostream>
#include<string.h>

using std::cin;
using std::cout;
using std::endl;

class Computer{
public:
    Computer(const char * brand, double price)
    :_price(price),
    _brand(brand)
    {
        /* strcpy(_brand, brand); */
        cout << "Computer的构造函数被调用了。" << endl;
    }

    ~Computer(){
        cout << "~Computer" << endl;
    }
private:
    const char * _brand;
    double _price;
};

void test(){
    Computer cmp("华为", 1999);
}

int main()
{
    test();

    return 0;
}

