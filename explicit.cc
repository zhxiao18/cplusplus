//explicit:防止隐式转换
#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    explicit
    Point(int x, int y)
    :_ix(x),
    _iy(y)
    {
        cout << "Point Init" << endl;
    }

    void print(){
        cout << "(" << _ix << "," << _iy << ")" << endl;
    }

    ~Point(){
        cout << "Point Destroy" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test01(){
    /* Point pt = 5;//error */
    /* pt.print(); */

    Point pt2(1,2);
    pt2.print();
}

int main()
{   
    test01();
    return 0;
}

