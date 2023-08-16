#include <iostream>
#include <vector>
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
using std::vector;
using std::istringstream;

typedef struct Record_t
{
    string _word;
    int _frequency;
}Record_s;

class Directory{
public:
    void read(const string &filename);
    void store(const string &filename);
private:
    vector<Record_s> _dict;
    string dealWorld(const string & world);
    void addVector(const string & world);
};

string Directory::dealWorld(const string & world){
    for(size_t idx = 0; idx != world.size(); ++idx){
        if(!isalpha(world[idx])){
            return string();
        }
    } 
    return world;
}

void Directory::addVector(const string & world){
    if(world == string()){
       return; 
    }

    for(size_t idx = 0; idx != _dict.size(); ++idx){
        if(_dict[idx]._word == world){
            _dict[idx]._frequency++;
            return;
        }
    }
    Record_t recd;
    recd._word = world;
    recd._frequency = 1;
    _dict.push_back(recd);
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

            //添加到Vector
            addVector(changeWord);
        }
    }
    ifs.close();
}

void Directory::store(const string & filename){
    ofstream ofs(filename.c_str());
    if(!ofs.good()){
        cerr << "ofstream is not good" << endl;
    }

    for(size_t idx = 0; idx != _dict.size(); ++idx){
        ofs << _dict[idx]._word << " " << _dict[idx]._frequency << endl;
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

