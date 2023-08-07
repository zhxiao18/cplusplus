#include <iostream>
#include <string>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void test01(){
    string str1 = "hello";
    string str2 = "world";
    string str3 = str1 + str2;      //不需要考虑内存
    cout << "str1: " << str1 <<endl
        << "str2: " << str2 << endl
        << "str3: " << str3 << endl;

    //C++风格字符串 -> c风格字符串
    const char * pstr = str3.c_str();
    cout << "pstr: " << pstr << endl;

    //获取C++风格字符串的长度
    int len1 = str3.size();
    cout << "str len1 = " << len1 << endl;
    int len2 = str3.length();
    cout << "str len2 = " << len2 << endl;

    //遍历C++字符串
    for(int i = 0; i != str3.size(); i++){
        cout << str3[i] << "  ";
    }
    cout << endl;

    //自符串拼接
    string str4 = str3 + " wangdao";
    cout << "str4 : " <<  str4 << endl;

    string str5 = str4 + 'A';
    cout << "str5: " << str5 << endl;

    str5.append(str1);
    cout << "str5: " << str5 << endl;

    // is empty
    string str;
    cout << "Empty: " << str.empty() << endl;
}

int main()
{   
    test01();
    return 0;
}

