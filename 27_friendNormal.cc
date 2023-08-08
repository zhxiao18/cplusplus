#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>

using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    Point(int x, int y)
    :_ix(x), _iy(y)
    {
        cout << "Point init" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test01(){
    cout << "------------------------------------------------------------------" << endl;
}

int main()
{   
    Point pt1(0,0);
    Point pt2(3,4);
    test01();
    return 0;
}

