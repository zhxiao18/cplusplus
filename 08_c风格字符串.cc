#include <iostream>
#include<string.h>
#include<stdio.h>

using std::cin;
using std::cout;
using std::endl;

void test(){
    char arr1[] = "hello,world";
    const char * pstr = "hello shenzhen";
    cout << arr1 << endl;
    cout << sizeof(arr1) << endl;
    cout << strlen(arr1) << endl;
    printf("%p\n", pstr);
    cout << &pstr << endl;
}

int main()
{
    test();

    return 0;
}

