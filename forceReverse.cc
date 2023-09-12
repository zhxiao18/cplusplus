#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

void test01(){
    int i_number = 19;
    double d_number = 10.3;

    //把double类型转换成int型
    i_number = static_cast<int>(d_number);
    cout << "i_number = " << i_number << endl;
    cout << "-----------------------" << endl;

    //把int*型转换成void*型
    //delete pInt;
    int *pInt = new int(12);
    void *pVoid = static_cast<void*>(pInt);
    cout << pVoid << endl;
    delete pInt;
}

void test02(){
    const int number = 10;
    /* int *pInt = &number; */  //error, number is const
    int *pInt = const_cast<int*>(&number);
    *pInt = 20;         //未定义行为

    cout << "number = " << number << endl;      //10
    cout << "*pInt = " << *pInt << endl;        //20

    printf("&number = %p\n", &number);          //0x7ffc0259f47c
    printf("pInt = %p\n", pInt);                //0x7ffc0259f47c  
}

int main()
{   
    /* test01(); */
    test02();
    return 0;
}

