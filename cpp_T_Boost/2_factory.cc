#include <math.h>
#include <iostream>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;

//抽象类
class Figure
{
public:
    //声明了两个纯虚函数
    virtual void display() const = 0;
    virtual double area() const = 0;

    virtual ~Figure() {}
};

class Rectangle
: public Figure
{
public:
    Rectangle(double length = 0.0, double width = 0.0)
    : _length(length)
    , _width(width)
    {
        cout << "Rectangle(double = 0.0, double = 0.0)" << endl;
    }

    virtual void display() const override
    {
        cout << "Rectangle: ";
    }

    virtual double area() const override
    {
        return _width * _length;
    }

    ~Rectangle()
    {
        cout << "~Rectangle()" << endl;
    }
private:
    double _length;
    double _width;
};

//Circle cir = 10;
class Circle
: public Figure
{
public:
    explicit
    Circle(double radius = 0.0)
    : _radius(radius)
    {
        cout << "Circle(double = 0.0)" << endl;
    }

    virtual void display() const override
    {
        cout << "Circle: ";
    }

    virtual double area() const override
    {
        return 3.14 * _radius * _radius;
    }

    ~Circle()
    {
        cout << "~Circle()" << endl;
    }

private:
    double _radius;
};

class Triangle
: public Figure
{
public:
    Triangle(double a= 0.0, double b = 0.0, double c = 0.0)
    : _a(a)
    , _b(b)
    , _c(c)
    {
        cout << "Triangle(double = 0.0, double = 0.0, double = 0.0)" << endl;
    }

    virtual void display() const override
    {
        cout << "Triangle: ";
    }

    virtual double area() const override
    {
        double tmp = (_a + _b + _c)/2;
        
        return sqrt(tmp * (tmp - _a) * (tmp - _b) * (tmp - _c));
    }

    ~Triangle()
    {
        cout << "~Triangle()" << endl;
    }

private:
    double _a;
    double _b;
    double _c;
};

void func(Figure *pfig)
{
    pfig->display();
    cout << " 的面积: " << pfig->area() << endl;
}

//工厂方法
//优点
//1、满足了单一职责原则
//2、满足了开闭原则，不能更好的扩展
//3、满足了依赖导致原则（面向抽象编程）
//
//缺点：
//工厂的个数会随着产品的数目的增加而急剧增加
class Factory
{
public:
    virtual Figure *get() = 0;
    virtual ~Factory() {}
};

class RectangleFactory
: public Factory
{
public:
    RectangleFactory()
    {
        cout << "RectangleFactory()" << endl;
    }
    Figure *get() override
    {
        //都是从配置文件中读取出来
        //配置文件的形式.txt、.conf、xml、yang
        //需要读取配置文件，然后获取对应的数据
        Rectangle *prec = new Rectangle(10, 20);
        return prec;
    }

    ~RectangleFactory()
    {
        cout << "~RectangleFactory()" << endl;
    }
};

class CircleFactory
: public Factory
{
public:
    CircleFactory()
    {
        cout << "CircleFactory()" << endl;
    }

    Figure *get() override
    {
        //都是从配置文件中读取出来
        //配置文件的形式.txt、.conf、xml、yang
        //需要读取配置文件，然后获取对应的数据
        Circle *pcir = new Circle(10);
        return pcir;
    }

    ~CircleFactory()
    {
        cout << "~CircleFactory()" << endl;
    }
};

class TriangleFactory
: public Factory
{
public:
    TriangleFactory()
    {
        cout << "TriangleFactory()" << endl;
    }

    Figure *get() override
    {
        //都是从配置文件中读取出来
        //配置文件的形式.txt、.conf、xml、yang
        //需要读取配置文件，然后获取对应的数据
        Triangle *ptri = new Triangle(3, 4, 5);
        return ptri;
    }

    ~TriangleFactory()
    {
        cout << "~TriangleFactory()" << endl;
    }
};

int main(int argc, char *argv[])
{
    unique_ptr<Factory> recFac(new RectangleFactory());
    unique_ptr<Figure> prec(recFac->get());

    unique_ptr<Factory> cirFac(new CircleFactory());
    unique_ptr<Figure> pcir(cirFac->get());

    unique_ptr<Factory> triFac(new TriangleFactory());
    unique_ptr<Figure> ptri(triFac->get());

    func(prec.get());
    func(pcir.get());
    func(ptri.get());

    return 0;
}

