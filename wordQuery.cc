#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;
using std::vector;
using std::set;
using std::map;
using std::string;

class TextQuery{
public:
    void readFile(const string & filename);
    void query(const string & world);
private:
    vector<string> _line;
    map<string, set<int> > _word_numbers;
    map<string, int> _dist;

    string dealWorld(const string & world);
};

string TextQuery::dealWorld(const string & word){
    for(size_t idx = 0; idx != word.size(); ++idx){
        if(!isalpha(word[idx])){
            return string();
        }
    }    
    return word;
}

void TextQuery::readFile(const string & filename){
    ifstream ifs(filename.c_str());
    if(!ifs.good()){
        cout << "ifstream not good" << endl;
        return;
    }

    string line;
    int lineNum = 0;
    while(getline(ifs, line)){
        _line.push_back(line);

        istringstream iss(line);

        string word;
        while(iss >> word){
            string changeWord = dealWorld(word);

            if(changeWord == string()){
                break;
            }
            //统计单词词频
            ++_dist[word];
            //记录单词所在行
            _word_numbers[word].insert(lineNum);
        }
        lineNum++;
    }
    cout << _dist.size() << endl;
    ifs.close();
}

void TextQuery::query(const string & world ){
        cout << "----------------------------------" << endl;
        int count = _dist[world];
        cout << world << "occurs" << count << "times." << endl;

        set<int> lines = _word_numbers[world];
        for(auto &elem : lines){
            cout << "(line " << elem + 1 << ") " << _line[elem] << "." << endl;
        }
        cout << "------------------------------------" << endl;
}

int main(int argc, char * argv[])
{   
    // ./a.out The_Holy_Bible.txt hello 
    TextQuery tq;
    tq.readFile(argv[1]);
    while(1){
        cout << "Input world" << endl;
        string word;
        cin >> word;
        tq.query(word);
    }
    return 0;
}

