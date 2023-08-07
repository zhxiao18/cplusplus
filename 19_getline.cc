#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

void test01(){
    ifstream ifs("test.cc");
    if(!ifs.good()){
        cout << "file is not good" << endl;
        return ;
    }

    string word;
    while(getline(ifs, word)){
        cout << word << endl;
    }
    cout << endl;
}

int main()
{   
    test01();
    return 0;
}

