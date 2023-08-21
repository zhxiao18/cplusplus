//异常处理
#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

void test01(){
    int x, y;
    cin >> x >> y;
    try{
        if(0 == y){
            throw y;
        }else{
            cout << "(x/y) = " << x/y << endl;
        }
    }catch(int x){
        cout << "catch(x)" << endl;
    }catch(double y){
        cout << "double(y)" << endl;
    }
}

int main()
{   
    test01();
    return 0;
}

