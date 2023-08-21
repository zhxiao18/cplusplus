#ifndef __CLASSDEMO__
#define __CLASSDEMO__

/* #include <iostream> */
/* #include <string.h> */

using namespace std;

class Computer{
public:
    Computer();
    ~Computer();
    void setBrand(const char * brand);
    void setPrice(float price);
    void print();
private:
    char _brand[20];
    float _price;
};

#endif

