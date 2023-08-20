#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;
//可变模板参数

template <typename ...Args>
void func(Args ...args){
    cout << "sizeof(...Args) = " << sizeof...(Args) << endl; 
    cout << "sizeof(...args) = " << sizeof...(args) << endl; 
}

void test01(){
    func();
    func(1);
}

int main()
{   
    test01();
    return 0;
}

