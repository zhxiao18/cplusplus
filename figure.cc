#include <math.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

//编写程序：给定以下抽象类Figure，通过该图形类扩展生成3个不同的图形Rectangle、Circle、Triangle

class Figure{
public:
    virtual string getName() const = 0;
    virtual double getArea() const = 0;
};

class Rectangle
:public Figure
{
public:
    Rectangle(const double & length, const double & width)
    :_length(length),
    _width(width)
    {
        cout << "Rectangle(const double length, const double width)" << endl;
    }
    string getName() const{
        return "Rectangle";
    }

    double getArea() const{
        return _length * _width;
    }
private:
    double _length;
    double _width;
};

class Circle
:public Figure
{
public:
    Circle(const double & radius)
    :_radius(radius)
    {
        cout << "Circle(const double & radius)" << endl;
    }

    string getName() const{
        return "Circle";
    }

    double getArea() const{
        return 3.14 * _radius * _radius;
    }
private:
    double _radius;
};

class Triangle
:public Figure
{
public:
    Triangle(const double & sidex, const double & sidey, const double & sidez)
    :_sidex(sidex),
    _sidey(sidey),
    _sidez(sidez)
    {
        cout << "Triangle(const double & sidex, const double & sidey, const double & sidez)" << endl;
    }
    string getName() const{
        return "Triangle";
    }

    double getArea() const{
        double tmp = (_sidex + _sidey + _sidez) / 2;
        return sqrt(tmp * (tmp - _sidex) * (tmp - _sidey) * (tmp - _sidez));
    }
private:
    double _sidex;
    double _sidey;
    double _sidez;
};

void display(Figure & fig){
    cout << fig.getName() << "的面积是：" << fig.getArea() << endl;
}

void test01(){
    Rectangle r(10, 20);
    Circle c(15);
    Triangle t(3,4,5);

    display(r);
    display(c);
    display(t);
}

int main()
{   
    test01();
    return 0;
}

