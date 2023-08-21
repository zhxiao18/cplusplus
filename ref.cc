#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

void swap(int &x, int &y){
    int temp = x;
    x = y;
    y = temp;
}

#if 0
void test01(){
    int a = 3, b = 4;
    swap(a, b);
    cout << "a = " << a <<endl;
    cout << "b = " << b << endl;
}
#endif

int arr[5] = {1,2,3,4,5};
int &getIdx(int idx){
    return arr[idx];
}

void test02(){
    cout << "getIdx[0] = " << getIdx(0) << endl;
    getIdx(0) = 10;
    cout << "arr[0] = " << arr[0] << endl;
    cout << "getIdx[0] = " << getIdx(0) << endl;
}

int num = 20;
int &point(int val){
    num = val;
    return num;
}
void test03(){
    cout << "num = " << point(100) << endl;
}


int main()
{   
    /* test01(); */
    /* test02(); */
    test03();
    return 0;
}

