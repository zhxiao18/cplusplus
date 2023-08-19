#include <iostream>
#include <string.h>
#include <string>
#include <memory>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::vector;

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
    unique_ptr<int> up(new int(10));
    cout << "*up: " << *up << endl;
    cout << "up.get(): " << up.get() << endl; //up.get(): 0x55b7af45be70
    /* unique_ptr<int> up2 = up; */ //不允许复制：unique_ptr(const unique_ptr&) = delete;

    unique_ptr<int> up3(new int(20));
     /* up3 = up; */ //error,不允许赋值，unique_ptr& operator=(const unique_ptr&) = delete; 

    cout << "---------------------" << endl;
    vector<unique_ptr<int>> vec;
    /* vec.push_back(up3); */ //error
    vec.push_back(std::move(up));//具备移动语义，可以传右值
    vec.push_back(unique_ptr<int>(new int(20)));

    vector<unique_ptr<Point>> vec2;
    unique_ptr<Point> up4(new Point(5,6));
    vec2.push_back(std::move(up4));//执行unique_ptr的构造函数
    vec2.push_back(unique_ptr<Point>(new Point(10,20)));

    vec2[0]->print();//(5,6)
    vec2[1]->print();
}

int main()
{   
    test01();
    return 0;
}

