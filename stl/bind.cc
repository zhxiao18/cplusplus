#include <iostream>
#include <functional>

using std::cin;
using std::cout;
using std::endl;
using std::bind;
using std::function;

int add(int x, int y, int z){
    cout << "add(int,int,int)" << endl;
    return x + y + z;
}

class Example{
public:
    int add(int x, int y){
        cout << "Example::add(int,int)" << endl;
        return x + y;
    }

    static int func(int x, int y){
        cout << "static func(int,int)" << endl;
        return x + y;
    }
};

void test01(){
    //bind绑定普通函数
    /* auto f = bind(add, 1, 2, 3); */
    //bind改变了函数的形态，使用可以直接f()，不用传递参数
    function<int()> f = bind(add, 1, 2, 3); //函数容器
    cout << "f = " << f() << endl; //6

    //绑定非静态成员函数
    Example ex;
    /* auto f2 = bind(&Example::add,&ex ,3,4); */
    function<int()> f2 = bind(&Example::add,&ex ,3,4);
    cout << "f2 = " << f2() << endl; //7

    //bind绑定静态成员函数
    /* auto f3 = bind(&Example::func, 5,6); */
    function<int()> f3 = bind(&Example::func, 5,6);
    cout << "f3 = " << f3() << endl; //11

    //占位参数
    using namespace std::placeholders;
    /* auto f4 = bind(add, _1, _2, _4); */
    function<int(int,int)> f4 = bind(add, 10, _1, _2);
    cout << "f4(10, 20, 60) = " << f4( 30, 60) << endl; //100
}

int main()
{   
    test01();
    return 0;
}

