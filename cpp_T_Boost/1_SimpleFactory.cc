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

//优点：根据产品的名字就能生产出对应的产品，同时一个工厂可以
//生产多种类型的产品
//缺点：
//1、违背了单一职责原则
//2、违背了开闭原则，不能更好的扩展
//3、违背了依赖导致原则（面向抽象编程）
class Factory
{
public:
    static Figure *get(const string &name)
    {
        if(name == "rectangle")
        {
            //都是从配置文件中读取出来
            //配置文件的形式.txt、.conf、xml、yang
            //需要读取配置文件，然后获取对应的数据
            Rectangle *prec = new Rectangle(10, 20);
            return prec;
        }
        else if(name == "circle")
        {
            //都是从配置文件中读取出来
            //配置文件的形式.txt、.conf、xml、yang
            //需要读取配置文件，然后获取对应的数据
            Circle *pcir = new Circle(10);
            return pcir;
        }
        else if(name == "triangle")
        {
            //都是从配置文件中读取出来
            //配置文件的形式.txt、.conf、xml、yang
            //需要读取配置文件，然后获取对应的数据
            Triangle *ptri = new Triangle(3, 4, 5);
            return ptri;
        }
        else if(name == "")
        {

        }
        else
        {
            return nullptr;
        }
    }
#if 0
    static Figure *getRectangle()
    {
        //都是从配置文件中读取出来
        //配置文件的形式.txt、.conf、xml、yang
        //需要读取配置文件，然后获取对应的数据
        Rectangle *prec = new Rectangle(10, 20);
        return prec;
    }
    
    static Figure *getCircle()
    {
        //都是从配置文件中读取出来
        //配置文件的形式.txt、.conf、xml、yang
        //需要读取配置文件，然后获取对应的数据
        Circle *pcir = new Circle(10);
        return pcir;
    }
    
    static Figure *getTriangle()
    {
        //都是从配置文件中读取出来
        //配置文件的形式.txt、.conf、xml、yang
        //需要读取配置文件，然后获取对应的数据
        Triangle *ptri = new Triangle(3, 4, 5);
        return ptri;
    }
#endif

};

#if 0
Figure *getRectangle()
{
    //都是从配置文件中读取出来
    //配置文件的形式.txt、.conf、xml、yang
    //需要读取配置文件，然后获取对应的数据
    Rectangle *prec = new Rectangle(10, 20);
    return prec;
}

Figure *getCircle()
{
    //都是从配置文件中读取出来
    //配置文件的形式.txt、.conf、xml、yang
    //需要读取配置文件，然后获取对应的数据
    Circle *pcir = new Circle(10);
    return pcir;
}

Figure *getTriangle()
{
    //都是从配置文件中读取出来
    //配置文件的形式.txt、.conf、xml、yang
    //需要读取配置文件，然后获取对应的数据
    Triangle *ptri = new Triangle(3, 4, 5);
    return ptri;
}
#endif
int main(int argc, char *argv[])
{
    unique_ptr<Figure> prec(Factory::get("rectangle"));
    unique_ptr<Figure> pcir(Factory::get("circle"));
    unique_ptr<Figure> ptri(Factory::get("triangle"));

    func(prec.get());
    func(pcir.get());
    func(ptri.get());

    return 0;
}

