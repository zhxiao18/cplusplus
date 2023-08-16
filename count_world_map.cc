#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::string;
using std::map;
using std::istringstream;

class Directory{
public:
    void read(const string &filename);
    void store(const string &filename);
private:
    map<string,int> _dict;
    string dealWorld(const string & world);
    void addMap(const string & world);
};

string Directory::dealWorld(const string & world){
    for(size_t idx = 0; idx != world.size(); ++idx){
        if(!isalpha(world[idx])){
            return string();
        }
    } 
    return world;
}

void Directory::addMap(const string & world){
    if(world == string()){
       return; 
    }
    ++_dict[world];
}

void Directory::read(const string &filename){
    ifstream ifs(filename.c_str());
    if(!ifs.good()){
        cerr << "ifstream is not good" << endl;
        return;
    }
    string line;
    
    while(getline(ifs, line)){
        istringstream iss(line);

        string world;
        while(iss >> world){
            //判断是否合法
            string changeWord = dealWorld(world);

            //添加到map
            addMap(changeWord);
        }
    }
    ifs.close();
}

void Directory::store(const string & filename){
    ofstream ofs(filename.c_str());
    if(!ofs.good()){
        cerr << "ofstream is not good" << endl;
        return;
    }

    map<string, int>::iterator it;
    for(it = _dict.begin(); it != _dict.end(); ++it){
        ofs << it->first << " " << it->second << endl;
    }

    ofs.close();
}

int main(int argc, char * argv[])
{   
    Directory dect;
    dect.read(argv[1]);
    dect.store(argv[2]);
    return 0;
}

