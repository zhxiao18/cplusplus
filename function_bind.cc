#include <iostream>
#include <functional>

using std::cout;
using std::endl;
using std::function;
using std::bind;

class Figure
{
public:
    using DisplayCallback = function<void()>;
    using ArerCallback = function<double()>;

    //注册回调函数
    void setDisplayCallback(DisplayCallback && cb){
        _displaycallback = std::move(cb);
    }

    void setAreaCallback(ArerCallback && cb){
        _areacallback = std::move(cb);
    }

    //执行回调函数
    void dealDisplayCallback(){
        if(_displaycallback){
            _displaycallback();
        }
    }

    double dealAreaCallback(){
        if(_areacallback){
            return _areacallback();
        }else{
            return 0.0;
        }
    }
private:
    DisplayCallback _displaycallback;
    ArerCallback _areacallback;
};

class Rectangle
{
public:
    Rectangle(double length = 0.0, double width = 0.0)
    : _length(length)
    , _width(width)
    {
        cout << "Rectangle(double = 0.0, double = 0.0)" << endl;
    }

    void display(int x) const 
    {
        cout << "Rectangle";
    }

    double area() const 
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

class Circle
{
public:
    explicit
    Circle(double radius = 0.0)
    : _radius(radius)
    {
        cout << "Circle(double = 0.0)" << endl;
    }

    void show() const 
    {
        cout << "Circle";
    }

    double showArea() const 
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

void func(Figure & fig){
    fig.dealDisplayCallback();
    cout << " 的面积：" << fig.dealAreaCallback() << endl;
}

int main()
{
    Rectangle rec(12,20);
    Circle cir(3.43);

    Figure fig;
    fig.setDisplayCallback(bind(&Rectangle::display,&rec,10));
    fig.setAreaCallback(bind(&Rectangle::area,&rec));
    func(fig);

    fig.setDisplayCallback(bind(&Circle::show,&cir));
    fig.setAreaCallback(bind(&Circle::showArea,&cir));
    func(fig);
    return 0;
}

