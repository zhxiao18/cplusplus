#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;
//可变模板参数
template <typename ...Args> //Args:模板参数包
void func(Args ...args){//args:函数参数包
    cout << "sizeof(...Args) = " << sizeof...(Args) << endl; 
    cout << "sizeof(...args) = " << sizeof...(args) << endl; 
}

void print(){
    cout << endl;
}

template<typename T, typename ...Args>
void print(T t, Args ...args){
    cout << t << " ";
    print(args...);
}

void test01(){
    /* func(); */
    /* func(1); */

    print(1,"hello", true, 3.3);
}

int main()
{   
    test01();
    return 0;
}

