#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>
#include <memory>

using std::cin;
using std::cout;
using std::endl;
using std::string;

class Point{
public:
    Point(int ix, int iy)
    :_ix(ix),
    _iy(iy)
    {
        cout << "Point(int ix, int iy)" << endl;
    }

    void print(){
        cout << "(" << _ix << "," << _iy << ")" << endl;
    }

    ~Point(){
        cout << "~Point()" << endl;
    }
private:
    int _ix;
    int _iy;
};

void test01(){
    //智能指针
    std::auto_ptr<Point> ap(new Point(1,2));
    ap->print();
    /* Point *p = new Point(1,2); */
    /* p->print(); */
    cout << endl;

    //pInt:裸指针
    int *pInt = new int(10);
    std::auto_ptr<int> ap2(pInt);
    cout << "*ap: " << &ap2 << endl;
}

int main()
{   
    test01();
    return 0;
}

