#include <iostream>
#include<stdio.h>

using std::cin;
using std::cout;
using std::endl;

int g_number = 10;

void test(){
    int l_number = 20;
    static int s_number = 30;
    const char* p = "point string";
    char * pstr = new char[10]();

    cout << "临时变量(栈区)：&l_number:" << &l_number << endl;
    cout << "(指针地址，栈区)&p:" << &p << endl;
    printf("(堆区)pstr:%p\n", pstr);
    cout << "全局变量：&g_number:" << &g_number << endl;
    cout << "(静态变量)&static:" << &s_number << endl;
    printf("(文字常量)&p:%p\n", p);
    cout << "(程序代码)&test():" << &test << endl;
    delete  [] pstr;
}

int main()
{
    test();
    cout << "(程序代码)&main():" << &main << endl;
    return 0;
}

