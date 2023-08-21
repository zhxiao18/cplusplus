#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using std::cin;
using std::cout;
using std::endl;

void test01(){
    //malloc/free
    int *pInt = (int *)malloc(sizeof(int));
    bzero(pInt, sizeof(int));
    *pInt = 10;
    cout << "*pInt = " << *pInt << endl;
    free(pInt);
    pInt = nullptr;

    int *arr = new int(10);
    cout << "arr = " << *arr << endl;
    delete arr;
    arr = nullptr;
}

int main()
{   
    test01();
    return 0;
}

