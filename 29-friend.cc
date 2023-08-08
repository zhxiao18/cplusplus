#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;

/* class Computer{ */
/* public: */
/*     void setBrand(const char * brand){ */
/*         strcpy(_brand, brand); */
/*     } */
/*     void setPrice(float price){ */
/*         _price = price; */
/*     } */
/*     friend void test01();   //全局函数做友元 */
/* private: */
/*     char _brand[20]; */
/*     float _price; */
/* }; */

/* //全局函数做友元 */
/* void test01(){ */
/*   Computer cmp; */
/*   cmp.setBrand("华为"); */
/*   cmp.setPrice(1999.9); */
/*   cout << cmp._brand << endl << cmp._price << endl; */
/* } */

class Point{
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
    
    //全局函数做友元
    friend float distance(const Point & lhs, const Point & rhs);

    friend float Line::distance(const Point & lhs, const Point & rhs);

private:
    int _ix;
    int _iy;
};

class Line{
public:
    float distance(const Point & lhs, const Point & rhs){
        return hypot(lhs._ix - rhs._ix, lhs._iy - rhs._iy);
    }
};

//全局函数做友元
float distance(const Point & lhs, const Point & rhs){
    return hypot(lhs._ix - rhs._ix, lhs._iy - rhs._iy); 
}

void test01(){
    Point p1(0,0);
    Point p2(3,4);
    cout << distance(p1, p2) << endl;
}

int main()
{   
    test01();
    return 0;
}

