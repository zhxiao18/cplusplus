#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

class Point {
public:
    Point(int x, int y)
    :_ix(x),
    _iy(y)
    {
        cout << "Point(int, int)" << endl;
    }

    int getY(){
        return _iy;
    }
protected:
    int _ix;
private:
    int _iy;
};

class Point3D : public Point{
public:
    Point3D(int x = 0, int y = 0, int z = 0)
    :Point(x, y),//不能被继承，但是可以被访问
    _iz(z)
    {
        cout << "Point3D(int x = 0, int y = 0, int z = 0)" << endl;
    }

    void print(){
        cout << "(" << _ix << "," << getY() << "," << _iz << ")" << endl;
    }
private:
    int _iz;
};

void test01(){
    Point3D p3d(1,2,3);
    p3d.print();
}

int main()
{   
    test01();
    return 0;
}

