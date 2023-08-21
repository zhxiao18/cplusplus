#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;
using std::flush;

void test01(){

#if 0
    //1.程序正常结束后，刷新缓冲区
    for(size_t idx = 0; idx < 1024; idx ++){
        cout << 'a' ;
    } 
#endif

#if 0
    //2.缓冲区满，先输出1024个a，然后程序结束，输出123
    for(size_t idx = 0; idx < 1024; idx ++){
        cout << 'a' ;
    } 
    cout << "123";

#endif

    //3.endl立马刷新，换行
    /* cout << "123" << endl; */

    //4.flush立马刷新，不换行
    cout << "123" << flush;
    sleep(3);
}

int main()
{   
    test01();
    return 0;
}

