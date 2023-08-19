#include <iostream>
#include <string.h>
#include <string>
#include <memory>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::shared_ptr;
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
    shared_ptr<int> sp(new int(10));
    cout << "*sp: " << *sp << endl;
    cout << "sp.get(): " << sp.get() << endl;
    cout << "sp.use_count:" << sp.use_count() << endl;
    cout << endl;

    shared_ptr<int> sp2 = sp; //复制
    cout << "*sp: " << *sp << endl;
    cout << "*sp2: " << *sp2 << endl;
    cout << "sp.use_count:" << sp.use_count() << endl;
    cout << "sp2.use_count:" << sp2.use_count() << endl;
    cout << endl;

    shared_ptr<int> sp3(new int(20));
     sp3 = sp; //赋值
    cout << "*sp: " << *sp << endl;
    cout << "*sp3: " << *sp3 << endl;
    cout << "sp.use_count:" << sp.use_count() << endl;
    cout << "sp2.use_count:" << sp2.use_count() << endl;
    cout << "sp3.use_count:" << sp3.use_count() << endl;

    cout << "---------------------" << endl;
    vector<shared_ptr<int>> vec; //作为容器元素
    vec.push_back(sp3);  //可以传左值
    vec.push_back(std::move(sp));//也可以传右值
    vec.push_back(shared_ptr<int>(new int(20)));
    cout << "vec[0]:" << vec[0] << endl;
    cout << "*vec[0]:" << *vec[0] << endl;

    vector<shared_ptr<Point>> vec2;
    shared_ptr<Point> sp4(new Point(5,6));
    vec2.push_back(sp4);
    /* vec2.push_back(std::move(sp4));//执行shared_ptr的构造函数 */
    vec2.push_back(shared_ptr<Point>(new Point(10,20)));

    vec2[0]->print();//(5,6)
    vec2[1]->print();
}

int main()
{   
    test01();
    return 0;
}

