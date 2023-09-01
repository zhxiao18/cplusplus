#include <time.h>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void test01(){
    time_t now;
    cout << time(&now) << endl;
}

int main()
{   
    test01();
    return 0;
}

