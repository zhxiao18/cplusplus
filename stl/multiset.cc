#include <iostream>
#include <string.h>
#include <stdio.h>
#include <set>

using std::cin;
using std::cout;
using std::endl;
using std::multiset;
using std::set;

template<typename container>
void printContainer(const container & con){
    for(auto & elem : con){
        cout << elem << " ";
    }
    cout  << endl;
}

void test01(){
    multiset<int> mset = {1,32,43,54,76,32,1,2,24,2};
    cout << "mset.size() => " << mset.size() << endl; //10

    set<int> mySet = {1,32,43,54,76,32,1,2,24,2};
    cout << "mySet.size() => " << mySet.size() << endl; //7
}

int main()
{   
    test01();
    return 0;
}

