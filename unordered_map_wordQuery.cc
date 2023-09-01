#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::ifstream;
using std::ofstream;
using std::istringstream;
using std::ostringstream;

class WordQuery{
public:
    WordQuery()
    {
        _line.reserve(200);
    }

    void readFile(const string & filename);
    void query(const string & word);
private:
    void prDealLine(string & line);
private:
    vector<string> _line;   //每行内容
    unordered_map<string,int> _wordCount;   //词频
    unordered_map<string, unordered_set<int>> _wordLine; //单词出现的行号
};

void WordQuery::readFile(const string & filename){
    ifstream ifs(filename);
    if(!ifs.good()){
        cerr << "file stream not good" << endl;
        return;
    }
    
    string line;
    size_t lineNum = 0;

    while(getline(ifs,line)){
        _line.push_back(line);

        prDealLine(line);

        string word;
        istringstream iss(line);
        while(iss >> word){
            ++_wordCount[word];
            _wordLine[word].insert(lineNum);
        }
        ++lineNum;
    }
}

void WordQuery::query(const string & word){
    int count = _wordCount[word];
    cout << "[" << word << "]" << " occurs " << count << " times." << endl;

    unordered_set<int> occurLines = _wordLine[word];
    for(auto & lineNo : occurLines){
        cout << "   (line " << lineNo + 1 << ") " << _line[lineNo]<< endl;
    }
}

void WordQuery::prDealLine(string & line){
    for(auto &elem : line){
        if(!isalpha(elem)){
            elem = ' ';
        }else if(isupper(elem)){
            elem = tolower(elem);
        }
    }
}

int main()
{   
    WordQuery wordquery;
    wordquery.readFile("The_Holy_Bible.txt");

    while(1){
        cout << "Please input query word: ";
        string word;
        cin >> word;
        cout << endl;
        wordquery.query(word);
    }
    return 0;
}

