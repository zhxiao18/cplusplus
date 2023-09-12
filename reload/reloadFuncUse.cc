//重载（）运算符
#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class FuncObject{
public:
    FuncObject()
    :_cnt(0)
    {
        cout << "FuncObject()" << endl;
    }

    int operator()(int val1, int val2){
        cout << "int operator()(int, int)" << endl;
        ++_cnt;
        return val1 + val2;
    }
private:
    int _cnt;
};

void test01(){
    FuncObject fo;
    int a = 3, b = 4;
    cout << "fo(a,b) |=> " << fo(a,b) << endl;
}

int main()
{   
    test01();
    return 0;
}

