#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
T add(T x, T y){
    return x + y;
}

template<>//模板的全特化
const char * add(const char * ps1, const char * ps2){
    cout << "const char * add(const char * ps1, const char * ps2)" << endl;
    size_t len = strlen(ps1) + strlen(ps2) + 1;
    /* char str[len]; */ 
    char * ptmp = new char[len]();
   strcpy(ptmp, ps1);
   strcat(ptmp, ps2);
   return ptmp;
}

void test01(){
    int a = 3, b = 4;
    double d1 = 3.2, d2 = 3.4;
    cout << "a + b: " << add(a,b) << endl;
    cout << "d1 + d2: " << add(d1,d2) << endl;
    cout << "-------------------------" << endl;

    const char * s1 = "hello";
    const char * s2 = "world";
    cout << "add(s1, s2): " << add(s1, s2) << endl;


}

int main()
{   
    test01();
    return 0;
}

