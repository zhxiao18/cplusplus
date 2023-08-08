#include "28-2classDemo.h"

#include <iostream>
#include <string.h>

using namespace std;

Computer::Computer(){
    cout << "Comouter Init" << endl;
}

void Computer::setBrand(const char * brand)
{
    strcpy(_brand, brand);
}

void Computer::setPrice(float price)
{
    _price = price;
}

void Computer::print()
{
    cout << "brand: " << _brand << endl
        << "price: " << _price << endl;
}

Computer::~Computer(){
    cout << "Computer destroy" << endl;
}
