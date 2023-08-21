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
using std::ifstream;
using std::ofstream;

void test01(){
    ifstream ifs("figure.cc");

    if(!ifs.good()){
        cerr << "file stream not good" << endl;
        return;
    }
    
    string word;
    while(getline(ifs, word)){
        cout << word << endl;
    }
    cout <<endl;

    ifs.close();
}

int main()
{   
    test01();
    return 0;
}

