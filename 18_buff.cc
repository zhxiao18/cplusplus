#include <iostream>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

using std::cin;
using std::cout;
using std::endl;

void test01(){
    for(size_t idx = 0; idx < 1024; idx ++){
        cout << 'a' ;
    } 
    cout << "123" << endl;
    sleep(3);
}

int main()
{   
    test01();
    return 0;
}

