//<</>> 运算符重载
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

class Complex{
    friend Complex operator+(const Complex & lhs, const Complex & rhs);
    /* friend Complex & operator+=(Complex & lhs, const Complex & rhs); */

    //友元函数重载 <<
    friend ostream & operator<<(ostream &os, const Complex & rhs);

    //友元重载 >>
    friend istream & operator >>(istream &is, Complex & rhs);
public:
    Complex(double real, double imag)
    :_real(real),
    _imag(imag)
    {
        cout << "Complex(double, double)" << endl;
    }
    Complex(){}
    /* void print(){ */
    /*     cout << _real << " + " << _imag  << "i" << endl; */
    /* } */

    //拷贝构造函数
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

//友元重载 +
Complex operator+(const Complex & lhs, const Complex & rhs){
    cout << ":Complex operator+(const Complex & , const Complex & )" << endl;
    return Complex(lhs._real + rhs._real, lhs._imag + rhs._imag);
}

#if 0 //友元形式重载 +=
Complex & operator+=(Complex & lhs, const Complex & rhs){
    cout << "Complex operator +=" << endl;
    lhs._real += rhs._real;
    lhs._imag += rhs._imag;
    return lhs;
}
#endif

//友元函数形式重载 <<
ostream & operator<<(ostream &os, const Complex & rhs)
{
    cout << "ostream & operator<<(ostream &os, const Complex & )" << endl;
    os << rhs._real << "+" << rhs._imag << "i" << endl; 
}
//---------------------------------------------
void readDouble(istream & is, double & number){
    while(is >> number, !is.eof()){
        if(is.bad()){
            std::cerr << "istream is bad" <<endl;
            return;
        }else if(is.fail()){
            is.clear();
            is.ignore(10240, '\n');
            cout << "please input double number" << endl;
        }else{
            cout << "number = " << number << endl;
            break;
        }
    }
}
istream & operator >>(istream &is, Complex & rhs){
    cout << "istream & operator >>" << endl;
    /* is >> rhs._real >> rhs._imag; */
    readDouble(is, rhs._real);
    readDouble(is, rhs._imag);
    return is;
}

void test01(){
    Complex cmp1(1,2);
    cout << cmp1;

    Complex cmp2(3,4);
    cout << cmp2;

#if 0
    /* cmp1 += cmp2; */ //等价
    operator+=(cmp1, cmp2);
    cmp1.print();
#endif

    cmp1 += cmp2;
    /* cmp1.print(); */
    cout << cmp1 << endl;;

#if 0
    Complex cmp3 = cmp1 + cmp2;
    cmp3.print();
#endif
}

void test02(){
    //重载 >>
    Complex c2;
    cin >> c2;
    cout << c2 << endl;
}

int main()
{   
    test02();
    return 0;
}

