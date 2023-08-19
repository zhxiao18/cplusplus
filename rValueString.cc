#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class String{
public:
    String(const char * pstr)
    :_pstr(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
    }

    //拷贝构造函数
    String(const String & rhs)
    :_pstr(new char[strlen(rhs._pstr) + 1]())
    {
        strcpy(_pstr, rhs._pstr);
        cout << "String(const String & rhs)" << endl;
    }

    //移动构造函数
    /* String str3 = "world"; */ //调用移动构造函数
    String(String && rhs)
    :_pstr(rhs._pstr)
    {
        rhs._pstr = nullptr;
        cout << "String(String && rhs)" << endl;
    }

    String &operator=(const String & rhs)
    {
        if(this != &rhs)
        {
            delete [] _pstr;
            _pstr = nullptr;

            _pstr = new char[strlen(rhs._pstr) + 1]();
            strcpy(_pstr, rhs._pstr);
        }
        cout << "String &operator=(const String & rhs)" << endl;
        return *this;
    }

    //移动赋值函数
    /* str3 = String("shenzhen"); */
    String &operator=(String && rhs){
        cout << "String &operator=(String && rhs)" << endl;
        if(this != &rhs){   //防止自移动
            delete [] _pstr;
            _pstr = nullptr;

            _pstr = rhs._pstr;
            rhs._pstr = nullptr;
        }
        return *this;
    }

    ~String(){
        if(_pstr){
            delete [] _pstr;
            _pstr = nullptr;
        }
        cout << "~String()" << endl;
    }

    friend std::ostream &operator<<(std::ostream &os, const String &rhs);
private:
    char * _pstr;
};

std::ostream &operator<<(std::ostream &os, const String &rhs){
    if(rhs._pstr){
        os << rhs._pstr;
    }
    return os;
}

void test01(){
    String str("hello");
    cout << "str: " << str << endl << endl;
    String str2 = str;
    cout << "str2: " << str2 << endl << endl;

    String str3 = "world";// "world",C风格字符串
    cout << "str3: " << str3 << endl << endl;
    //String(const char *) String(String && rhs) ~String() str3: world

    str3 = str; //String &operator=(const String & rhs)
    cout << "str3: " << str3 << endl << endl;

    str3 = String("shenzhen");
    cout << "str3: " << str3 << endl;
}   

int main()
{   
    test01();
    return 0;
}

