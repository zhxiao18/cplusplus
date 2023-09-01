#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::istream_iterator;
using std::copy;

void test01(){
    istream_iterator<int> isi(cin);
    vector<int> vec;
    copy(isi, istream_iterator<int>(), vec.begin());
}

int main()
{   
    test01();
    return 0;
}

