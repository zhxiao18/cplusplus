#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    Point(int ix, int iy)
    :_ix(ix),
    _iy(iy),
    ref(_ix)
    {
        ref = _ix;
        cout << "Point init" << endl;
        cout << "sizeof(ref)" <<  sizeof(ref) << endl;
    }
private:
    int _ix;
    int _iy;
    int &ref;
};

void test01(){
    Point point(3,5);
}

int main()
{   
    test01();
    return 0;
}

