#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <limits>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void printStreamStatus(){
    //判断流的状态
    cout << "cin.babit: " << cin.bad() << endl;
    cout << "cin.failbit: " << cin.fail() << endl;
    cout << "cin.eofbit: " << cin.eof() << endl;
    cout << "cin.goodbit: " << cin.good() << endl << endl;
}

void test01(){
    int number = 0;
    while(cin >> number, !cin.eof()){
        if(cin.bad()){
            cout << "不能恢复的流错误" << endl;
            return ;
        }else if(cin.fail()){
            //可以恢复的错误
            cin.clear();    //重置流状态
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "reset stream status." << endl;
        }else{
            cout << "number: " << number << endl;   
        }
    }
}

int main()
{   
    test01();
    return 0;
}

