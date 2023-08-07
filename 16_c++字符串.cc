#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

void test01(){
    cout << "-----------c string ----------------" << endl;
    //1、字符数组
    char str1[] = "hello";
    str1[0] = 'R';
    /* str1 = nullptr;     //指针常量 */
    cout << "str1:" << str1 << endl;
    //2、字符指针
    const char * str2 = "Hello";
    /* str2[0] = 'h'; */        //常量指针
    cout << "str2:" << str2 << endl;
    str2 = "wangdao";
    cout << "str2:" << str2 << endl;
    cout << "------------------------------------" << endl;


}

int main()
{   
    test01();
    return 0;
}

