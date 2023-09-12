//友元形式重载
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Complex{
    friend Complex operator+(const Complex & lhs, const Complex & rhs);
public:
    Complex(double real, double imag)
    :_real(real),
    _imag(imag)
    {
        cout << "Complex(double, double)" << endl;
    }

    void print(){
        cout << _real << " + " << _imag  << "i" << endl;
    }

    Complex(const Complex & rhs)
    :_real(rhs._real),
    _imag(rhs._imag)
    {
        cout << "Complex(const Complex &)" << endl;
    }

    ~Complex(){
        cout << "~Complex()" << endl;
    }
private:
    double _real;
    double _imag;
};

Complex operator+(const Complex & lhs, const Complex & rhs){
    cout << "3:Complex operator+(const Complex & lhs, const Complex & rhs)" << endl;
    return Complex(lhs._real + rhs._real, lhs._imag + rhs._imag);
}

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

