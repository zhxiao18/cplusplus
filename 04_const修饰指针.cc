#include<iostream>
using namespace std;

void test(){
    //指针常量
    /* int num1 = 10, num2= 20; */
    /* int *const p = &num1; */
    /* *p = 0; */
    /* p = &num2;  //error */
        
    //数组指针
    /* int arr[5] = {1,2,3,4,5}; */
    /* int (*p)[5] = &arr; */


    //指针数组
    /* int num1 = 10, num2 = 20, num3 = 30; */
    /* int *p1 = &num1, *p2 = &num2, *p3 = &num3; */
    /* int *arr[3] = {p1, p2, p3}; */
    /* for(int i = 0; i < 3; i ++){ */
    /*     cout << *arr[i] << endl; */
    /* } */
}

//函数指针
/* int add(int x, int y){ */
/*     return x + y; */
/* } */
/* int (*p)(int, int) = add; */
/* void test02(){ */
/*     cout << p(5,6) << endl; */
/* } */

//指针函数
int sum = 0;
int * add(int x, int y){
    sum = x + y;
    return &sum;
}
void test03(){
    cout << *add(5,5) << endl;
}

int main(int argc, char* argv[]){
    /* test(); */

    /* test02(); */

    test03();
    return 0;
}

