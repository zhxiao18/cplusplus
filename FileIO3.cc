//文件输入输出流
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::fstream;

void test01(){
    fstream fs("test.txt");

    if(!fs){
        cerr << "file stream not good" << endl;
        return;
    }
    
    //写入到文件中
    int number = 0;
    for(size_t idx = 1; idx != 6; ++idx){
        cin >> number;
        fs << number << " ";
    }

    //可以得到文件的大小，查看文件对象的位置
    //返回的是下一次进行正常操作的位置下标
    cout << "fs.tellg(): " <<  fs.tellg() << endl;
    cout << "fs.tellp(): " <<  fs.tellp() << endl;

    //文件偏移，把文件指针偏移到开头位置
    fs.seekg(0);// 绝对偏移
    /* fs.seekg(0,std::ios::beg); //相对开始偏移0个位置,beg/end/cur */

    //把文件输出到屏幕
    for(size_t idx = 0; idx != 6; ++idx){
        fs >> number;
        cout << number << " ";
    }
    cout << endl;

    fs.close();
}

int main()
{   
    test01();
    return 0;
}

