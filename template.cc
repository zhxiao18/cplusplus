//函数模板
#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;
#if 1 // //普通函数
template <typename T>
T add(T x, T y){
    return x + y;
}

//模板参数类型，设置默认值
//T：类型参数  kmax:非类型参数
template<typename T = double, int kmax = 10>
T multiply(T x, T y){
    cout << "T multiply(T, T)" << endl;
    return x * y * kmax;
}

//模板的全特化
template<>
const char * add(const char * ps1, const char * ps2){
    cout << "const char * add(const char * ps1, const char * ps2)" << endl;
    size_t len = strlen(ps1) + strlen(ps2) + 1;
    /* char str[len]; */ 
    char * ptmp = new char[len]();
   strcpy(ptmp, ps1);
   strcat(ptmp, ps2);
   return ptmp;
}

void test01(){
    int a = 3, b = 4;
    double d1 = 3.2, d2 = 3.4;

    cout << "a + b: " << add(a,b) << endl; //隐式实例化

    //显式实例化，就是将模板参数写出来
    cout << "d1 + d2: " << add<double>(d1,d2) << endl;
    cout << "-------------------------" << endl;

    const char * s1 = "hello";
    const char * s2 = "world";
    cout << "add(s1, s2): " << add(s1, s2) << endl;
}

void test02(){
    double d1 = 2.3;
    double d2 = 3.4;
    //普通调用,隐式实例化
    cout << "multiply(d1, d2) = " << multiply(d1, d2) << endl; 
    //显式实例化1（使用默认值）
    cout << "multiply(d1, d2) = " << multiply<double>(d1, d2) << endl; 
    //显式实例化2
    cout << "multiply(d1, d2) = " << multiply<double, 20>(d1, d2) << endl; 
    
}
#endif

#if 1 //成员模板

class Point{
public:
    Point(int ix = 0, int iy = 0)
    :_ix(ix),
    _iy(iy)
    {
        cout << "Point(int, int)" << endl;
    }

    //成员函数做模板
    template<typename T = int>
        T func(){
            return _ix;
        }

    ~Point(){
        cout << "~Point" <<endl;
    }
private:
    int _ix;
    int _iy;
};

void test03(){
    Point pt(1,2);
    cout << "pt.func() = " << pt.func() << endl;
    cout << "pt.func() = " << pt.func<int>() << endl;
}
#endif

int main()
{   
    /* test02(); */
    test03();
    return 0;
}

