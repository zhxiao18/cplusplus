//运算符重载：成员函数形式
#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Complex{
public:
    Complex(double real, double imag)
    :_real(real),
    _imag(imag)
    {
        cout << "Complex()" << endl;
    }

    void print(){
        cout << _real << " + " << _imag  << "i" << endl;
    }
    //运算符重载之成员函数
    Complex operator+(const Complex & rhs){
        cout << "Complex operator+(const Complex & rhs)" << endl;
        return Complex(_real + rhs._real, _imag + rhs._imag);
    }
    ~Complex(){
        cout << "~Complex()" << endl;
    }
private:
    double _real;
    double _imag;
};

void test01(){
    Complex cmp1(1,2);
    cmp1.print();

    Complex cmp2(3,4);
    cmp2.print();

    Complex cmp3 = cmp1 + cmp2;
    cmp3.print();
}

int main()
{   
    test01();
    return 0;
}

