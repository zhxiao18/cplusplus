//文件输出流
#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::clog;
using std::string;
using std::ifstream;
using std::ofstream;

void test01(){
    ifstream ifs("figure.cc");
    if(!ifs.good()){
        clog << "file stream not good" << endl;
        return;
    }

    ofstream ofs("test.txt");
    if(!ofs.good()){
        cout << "ofstream error" << endl;
        return;
    }

    string line;
    while(getline(ifs, line)){
        //把读出来的文件写入到另一个文件中
        ofs << line << endl;
    }
    
    ifs.close();
    ofs.close();
}

int main()
{   
    test01();
    return 0;
}

