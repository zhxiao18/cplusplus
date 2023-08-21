#include <iostream>
#include<string.h>

using std::cin;
using std::cout;
using std::endl;

class Computer{
public:
    void setBrand(const char* brand);
    void setPrice(double price);
    void print();
private:
    char _brand[20];
    double _price;
};

void Computer::setBrand(const char * brand){
    strcpy(_brand, brand);
}
void Computer::setPrice(double price){
    _price = price;
}
void Computer::print(){
    cout << "brand:" << _brand << endl;
    cout << "price:" << _price << endl;
}

int main()
{
    Computer cmp;
    cmp.setPrice(1999);
    cmp.setBrand("华为");
    cmp.print();

    return 0;
}

