//字符串IO
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::ostringstream;
using std::istringstream;
using std::ifstream;

#if 0 //ostringstream
string int_to_string(const int val){
    ostringstream oss;
    oss << val;
    //str函数可以将整数转换为字符串
    return oss.str();
}    
void test01(){
    string s1 = int_to_string(10);
    cout << "s1:" << s1 << endl; 
}
#endif

void readConfig(const string & filename){
    ifstream ifs(filename); 
    if(!ifs){
        cout << "open file error" << endl;
        return;
    }
    
    //istringstream
    string line;
    while(getline(ifs, line)){
        istringstream iss(line);
        string key;
        string value;
        /* while(iss >> key >> value){ */
        /*     cout << key << "->" << value << endl; */
        /* } */
        iss >> key >> value;
        cout << key << "->" << value << endl;
    }
    ifs.close();
}

int main()
{   
    /* test01(); */
    readConfig("myconfig.conf");
    return 0;
}

