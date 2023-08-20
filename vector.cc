#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::ifstream;
using std::vector;

void test01(){
    ifstream ifs("figure.cc");

    if(!ifs.good()){
        cerr << "file stream not good" << endl;
        return;
    }
    
    vector<string> vec;
    string line;
    while(getline(ifs, line)){
        //添加元素
        vec.push_back(line);
        cout << line << endl;
    }
    cout <<endl;

    ifs.close();

    cout << vec[30] << endl;
    
    //vec大小
    cout << "vec.size > " << vec.size() << endl;
    //容量
    cout << "vec.capacity > " <<  vec.capacity() << endl;
    //是否为空
    cout << "vec.empty > " << vec.empty() << endl;
    //首元素
    cout << "vec.front > " << vec.front() << endl;
}

int main()
{   
    test01();
    return 0;
}

