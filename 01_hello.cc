#include <iostream>

using std::cout;
using std::cin;
using std::endl;


/* using namespace std; */

namespace wd{

int num = 100;
void myPrintf(){
    cout<<"wd的输出"<<endl;
}

} // end

/* using namespace wd; */


using wd::myPrintf;
using wd::num;

//匿名空间
namespace {
void printf(const char* name, int a){
    cout<<"name :"<<name<<endl;
    cout<<"a = "<<a<<endl;
    cout << endl;
}
}

int main()
{
    /* //1.作用域限定符 */
    /* wd::myPrintf(); */
    /* cout<<wd::num<<endl; */

    //2.using 编译指令
    /* myPrintf(); */
    /* cout<<"using编译指令："<<num<<endl; */
    /* printf("zhangsan", 2); */
    
    int a = 10;
    int *p = &a;
    cout<<"*p = "<< p << endl;

    cout<<sizeof(char *)<<endl;

    /* int arr[10] = {1,2,3,4,5,6,7,8,9}; */
    /* int *p = arr; */
    
    /* for(int i = 0; i < 9; i ++){ */
    /*     cout<<*p+i<<endl; */
    /* } */
    
    printf("this is no name namespace", 10);

    return 0;
}

