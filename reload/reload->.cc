//重载->、.运算符
#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Data{
public:
    Data(int data)
    :_val(data)
    {
        cout << "Data(int)" << endl;
    }

    int getData(){
        return _val;
    }

    ~Data(){
        cout << "~Data" << endl;
    }
private:
    int _val;
};

class SecondLayer{
public:
    SecondLayer(Data * data)
    :_data(data)
    {
        cout << "SecondLayer(Data *)" << endl;
    }

    //->运算符重载
    Data * operator->(){
        return _data;
    }

    //解引用 运算符重载
    Data & operator*(){
        return *_data;
    }

    ~SecondLayer(){
        cout << "~SecondLayer()" << endl;
        if(_data){
            delete  _data;
            _data = nullptr;
        }
    }
private:
    Data *_data;
};

class ThirdLayer{
public:
    ThirdLayer(SecondLayer * sl)
    :_sl(sl)
    {
        cout << "ThirdLayer(SecondLayer *)" << endl;
    }

    //->运算符重载
    SecondLayer &operator->(){
        return *_sl;
    }

    ~ThirdLayer(){
        cout << "~ThirdLayer()" << endl;
    }
private:
    SecondLayer * _sl;
};

int main()
{   
    SecondLayer sl(new Data (10));
    /* cout << sl->getData() << endl; */
    cout << sl.operator->()->getData() << endl;
    cout << (*sl).getData() << endl;
    cout << sl.operator*().getData() << endl;

    ThirdLayer tl(new SecondLayer(new Data(20)));
    cout << tl->getData() << endl;
    cout << tl.operator->()->getData() << endl;

    return 0;
}

