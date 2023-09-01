#include <iostream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::make_pair;
using std::unordered_map;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::istringstream;

/* class WordTransform{ */
/* public: */
/*     void readFileTxt(const string & filename); */
/*     void readMapTxt(const string & filename); */
/* private: */
/*     unordered_map<string, string> _destWord;    //存放参照文本 */
/* }; */

/* void WordTransform::readFileTxt(const string & filename){ */
/*     ifstream ifs(filename); */
/*     string word; */
/*     while(ifs >>word){ */
/*         if(_destWord.count(word) != 0){ */
/*             cout << _destWord[word] << " "; */
/*         }else{ */
/*             cout << word << " "; */
/*         } */
/*     } */
/*     cout <<endl; */
/* } */
/* void WordTransform::readMapTxt(const string & filename){ */
/*     ifstream ifs(filename); */
/*     string key, val; */
/*     while(!ifs.eof()){ */
/*         ifs >> key; */
/*         getline(ifs,val); */
/*         _destWord.insert(make_pair(key,val)); */
/*     } */   
/* } */

/* int main() */
/* { */   
/*     WordTransform wdtf; */
/*     wdtf.readMapTxt("map.txt"); */
/*     wdtf.readFileTxt("file.txt"); */
/*     return 0; */
/* } */

class WordTrans
{
public:
    void builsMap(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs)
        {
            std::cerr << "open file " << filename << " error!" << endl;
            return;
        }

        string key;
        string word;
        while(ifs >> key && getline(ifs, word))
        {
            if(word.size() > 1)//判断空格
            {
                _um[key] = word.substr(1);//substr取子串
            }
        }

        ifs.close();
    }

    void trans(const string &filename)
    {
        ifstream ifs(filename);
        if(!ifs)
        {
            std::cerr << "open file " << filename << " error!" << endl;
            return;
        }

        string line;//接收一行的内容
        while(getline(ifs, line))
        {
            string word;
            istringstream iss(line);

            while(iss >> word)
            {
                auto it = _um.find(word);
                if(it != _um.end())
                {
                    cout << it->second;
                }
                else
                {
                    cout << word;
                }
                cout << " ";
            }
            cout << endl;
        }

        ifs.close();

    }
private:
    unordered_map<string, string> _um;//存放map.txt中的内容
};

int main(int argc, char *argv[])
{
    WordTrans wt;
    wt.builsMap("map.txt");
    wt.trans("file.txt");
    return 0;
}
