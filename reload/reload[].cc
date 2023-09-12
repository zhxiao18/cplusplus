//重载[]运算符
#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class charArr{
public:
    charArr(size_t size, const char * data)
    :_size(size),
    _data(new char[_size]())
    {
        cout << "charArr(size_t, const char *)" << endl;
        strcpy(_data, data);
    }

    char & operator [] (const size_t idx){
        if(idx >= _size){
            cout << "idx illegal" << endl;
            static char nullchar = '\0';
            return nullchar;
        }else{
            return _data[idx];
        }
    }

    ~charArr(){
        if(_data){
            delete [] _data;
            _data = nullptr;
        }
    }
private:
    size_t _size;
    char * _data;
};

void test01(){
    std::string str = "hello world";
    charArr charr(str.size() + 1,str.c_str());
    cout << str.size() << endl;
    for(int idx = 0; idx != str.size(); ++idx){
        /* cout << "charr.operator[](idx) => " << charr.operator[](idx) << endl; */ //原型
        cout << "charr[" << idx << "] => " << charr[idx] << endl; //简写形式  
    }
}

int main()
{   
    test01();
    return 0;
}

