#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Empty{
    private:
        int _ix;
};

void test01(){
    Empty emp;
    cout << "sizeof(empty) = " << sizeof(Empty) << endl;
    /* printf("&Empty:%p\n", &Empty); */
    cout << &emp << endl;
}

int main()
{   
    test01();
    return 0;
}

