#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

/* class Point;    //类的前向声明 */

/* class Line{ */
/* public: */
/*     float distance(const Point & lhs, const Point & rhs); */
/* //    Point pt; //field has incomplete type 'Point',point是不完整类型，不能创建对象 */
/*       /1* Point * ppt;//不完整类型可以创建指针 *1/ */
/* }; */

/* class Point{ */
/* public: */
/*     Point(int x, int y) */
/*     :_ix(x), */
/*     _iy(y) */
/*     { */
/*         cout << "Point Init" << endl; */
/*     } */

/*     ~Point(){ */
/*         cout << "Point Destroy" << endl; */
/*     } */
    
/*     //类函数做友元 */
/*     friend float Line::distance(const Point & lhs, const Point & rhs); */

/* private: */
/*     int _ix; */
/*     int _iy; */
/* }; */

/* //类函数做友元 */
/* float Line::distance(const Point & lhs, const Point & rhs){ */
/*     return hypot(lhs._ix - rhs._ix, lhs._iy - rhs._iy); */ 
/* } */

/* void test01(){ */
/*     Point p1(0,0); */
/*     Point p2(3,4); */

/*     cout << "distance: " << Line().distance(p1, p2) << endl; */
/* } */


class Point;    //类的前向声明

class Line{
public:
    float distance(const Point & lhs, const Point & rhs);
};

class Point{
    friend class Line;  //类做友元
public:
    Point(int x, int y)
    :_ix(x),
    _iy(y)
    {
        cout << "Point Init" << endl;
    }

    ~Point(){
        cout << "Point Destroy" << endl;
    }

private:
    int _ix;
    int _iy;
};

//类做友元
float Line::distance(const Point & lhs, const Point & rhs){
    return hypot(lhs._ix - rhs._ix, lhs._iy - rhs._iy); 
}

void test01(){
    Point p1(0,0);
    Point p2(3,4);

    cout << "distance: " << Line().distance(p1, p2) << endl;
}

int main()
{   
    test01();
    return 0;
}

