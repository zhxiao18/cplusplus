//+= 运算符重载
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Complex{
    friend Complex operator+(const Complex & lhs, const Complex & rhs);
    /* friend Complex & operator+=(Complex & lhs, const Complex & rhs); */
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

#if 1   //成员函数形式重载+=
    Complex & operator +=(const Complex & rhs){
        cout << "Complex & operator +=(const Complex &)" << endl;
        _real += rhs._real;
        _imag += rhs._imag;
        return *this;
    }
#endif

    ~Complex(){
        cout << "~Complex()" << endl;
    }
private:
    double _real;
    double _imag;
};

Complex operator+(const Complex & lhs, const Complex & rhs){
    cout << ":Complex operator+(const Complex & lhs, const Complex & rhs)" << endl;
    return Complex(lhs._real + rhs._real, lhs._imag + rhs._imag);
}

#if 0 //友元形式重载
Complex & operator+=(Complex & lhs, const Complex & rhs){
    cout << "Complex operator +=" << endl;
    lhs._real += rhs._real;
    lhs._imag += rhs._imag;
    return lhs;
}
#endif

void test01(){
    Complex cmp1(1,2);
    cmp1.print();

    Complex cmp2(3,4);
    cmp2.print();

#if 0
    /* cmp1 += cmp2; */ //等价
    operator+=(cmp1, cmp2);
    cmp1.print();
#endif

    cmp1 += cmp2;
    cmp1.print();

#if 0
    Complex cmp3 = cmp1 + cmp2;
    cmp3.print();
#endif
}

int main()
{   
    test01();
    return 0;
}

