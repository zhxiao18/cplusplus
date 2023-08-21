#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    Point(int x, int y)
    :_x(x),
    _y(y)
    {
        cout << "Point init" << endl;
    }

    void print(){
        cout << "(" << _x << "," << _y << ")" ;
    }

    ~Point(){
        cout << "~Point" << endl;
    }
private:
    int _x;
    int _y;
};

class Line{
public:
    Line(int x1, int y1, int x2, int y2)
    :_p1(x1, y1),
    _p2(x2, y2)
    {
        cout << "Line init" << endl;
    }

    void print(){
        _p1.print();
        cout << "---->";
        _p2.print();
        cout << endl;
    }

    ~Line(){
        cout << "~Line" << endl;
    }
private:
    Point _p1;
    Point _p2;
};

void test01(){
    Line line(1,2, 3, 4);
    line.print();
    
}

int main()
{   
    test01();
    return 0;
}

