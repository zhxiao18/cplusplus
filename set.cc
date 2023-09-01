//set的使用
#include <math.h>
#include <iostream>
#include <set>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::set;
using std::vector;
using std::pair;
using std::ostream;

template<typename container>
void display(const container & con){
    for(auto &elem : con){
        cout << elem << " ";
    }
    cout << endl;
}

void test01(){
    //创建对象
    set<int> number = {1,3,4,2,3,7,9,8,0,10};
    cout << "-------------遍历--------------" << endl;
    //遍历set元素
    //1、迭代器（泛型指针）
    set<int>::iterator it;
    for(it = number.begin(); it != number.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;

    //  2、auto
    /* for(auto &elem : number){ */
    /*     cout << elem << " "; */
    /* } */
    /* cout << endl; */

    cout << "------------find--------------" << endl;
    size_t cnt1 = number.count(11);
    size_t cnt2 = number.count(1);
    cout << "count: " << cnt1 << endl
        << "count: " << cnt2 << endl;
    
    /* set<int>::iterator it2 = number.find(1); */
    auto it2 = number.find(1);
    if(it2 == number.end()){
        cout << "not find" << endl;
    }else{
        cout << "find success: " << *it2 <<  endl;
    }

    cout << endl << "------------insert--------------" << endl;
    /* auto ret = number.insert(8); */  //等价
    cout << "-----1、插入单个元素insert(12)-----" << endl;
    display(number);
    pair<set<int>::iterator,bool> ret = number.insert(12);
    if(ret.second){
        cout << "该元素插入成功：" << *ret.first << endl;
    }else{
        cout << "insert error" << endl;
    }
    display(number);

    cout << "--2、插入一个迭代器范围的 vec = {32,43,56,76,85}--" << endl;
    vector<int> vec = {32,43,56,76,85};
    number.insert(vec.begin(), vec.end());
    cout << "number: ";
    display(number);

    cout << "-----insert 3:number -> {103,32,43,29}-----" << endl;
    display(number);
    number.insert({103,32,43,29});
    display(number);

    cout << endl << "------erase------" << endl;
    cout << "----erase(32)----" << endl;
    display(number);
    number.erase(32);
    display(number);

    cout << "----erase(it1,it2)----" << endl;
    display(number);
    set<int>::iterator it3 = number.begin();
    ++ it3;
    ++ it3;
    ++ it3;
    set<int>::iterator it4 = number.end();
    -- it4;
    -- it4;
    number.erase(it3,it4);
    display(number);

    cout << "------size------" << endl;
    cout << "size: " << number.size() << endl;
}

//---------------------------针对自定义类型-------------------------------------------

class Point{
public:
    Point(int ix, int iy)
    :_ix(ix),
    _iy(iy)
    {
        cout << "Point(int,int)" << endl;
    }

    friend ostream & operator<<(ostream &os,const Point & rhs);

    double distance() const{
        return hypot(_ix, _iy);
    }

    int getX() const{
        return _ix;
    }

    int getY() const {
        return _iy;
    }

/*     Point(const Point & rhs){ */
/*         _ix = rhs._ix; */
/*         _iy = rhs._iy; */
/*     } */

/*     Point(Point && rhs){ */
/*         _ix = rhs._ix; */
/*         _iy = rhs._iy; */
/*     } */

    ~Point(){
        cout << "~Point()" << endl;
    }
private:
    int _ix;
    int _iy;
};

ostream & operator<<(ostream &os,const Point & rhs){
    os << "(" << rhs._ix << "," << rhs._iy << ")";
    return os;
}

// --- -----------------std::less---------------
namespace std
{
//自定义类型：1、模板特化
template<>
struct less<Point>
{
    bool operator()(const Point & lhs, const Point & rhs){
        cout << "template<>operator()" << endl;
        if(lhs.distance() < rhs.distance()){
            return true;
        }else if(lhs.distance() == rhs.distance()){
            if(lhs.getX() < rhs.getX()){
                return true;
            }else if(lhs.getX() == rhs.getX()){
                if(lhs.getY() < rhs.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};
}
//自定义类型：2、函数对象
struct CompaerPointLess
{
    bool operator()(const Point & lhs, const Point & rhs){
        cout << "struct CompaerPointLess" << endl;
        if(lhs.distance() < rhs.distance()){
            return true;
        }else if(lhs.distance() == rhs.distance()){
            if(lhs.getX() < rhs.getX()){
                return true;
            }else if(lhs.getX() == rhs.getX()){
                if(lhs.getY() < rhs.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};

//自定义类型：3、重载运算符
bool operator < (const Point & lhs, const Point & rhs){
    cout << "bool operator < (const Point &, const Point &)" << endl;
    if(lhs.distance() < rhs.distance()){
        return true;
    }else if(lhs.distance() == rhs.distance()){
        if(lhs.getX() < rhs.getX()){
            return true;
        }else if(lhs.getX() == rhs.getX()){
            if(lhs.getY() < rhs.getY()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

//-----------------------------std::greater----------------
namespace std
{
//自定义类型：1、模板特化
template<>
struct greater<Point>
{
    bool operator()(const Point & lhs, const Point & rhs){
        cout << "template<>operator()" << endl;
        if(lhs.distance() > rhs.distance()){
            return true;
        }else if(lhs.distance() == rhs.distance()){
            if(lhs.getX() > rhs.getX()){
                return true;
            }else if(lhs.getX() == rhs.getX()){
                if(lhs.getY() > rhs.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};
}
//自定义类型：2、函数对象
struct CompaerPointGreater
{
    bool operator()(const Point & lhs, const Point & rhs){
        cout << "struct CompaerPointLess" << endl;
        if(lhs.distance() > rhs.distance()){
            return true;
        }else if(lhs.distance() == rhs.distance()){
            if(lhs.getX() > rhs.getX()){
                return true;
            }else if(lhs.getX() == rhs.getX()){
                if(lhs.getY() > rhs.getY()){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};

//自定义类型：3、重载运算符
bool operator > (const Point & lhs, const Point & rhs){
    cout << "bool operator < (const Point &, const Point &)" << endl;
    if(lhs.distance() > rhs.distance()){
        return true;
    }else if(lhs.distance() == rhs.distance()){
        if(lhs.getX() > rhs.getX()){
            return true;
        }else if(lhs.getX() == rhs.getX()){
            if(lhs.getY() > rhs.getY()){
                return true;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}

void test02(){
    /* set<Point> number = { */
    /* set<Point, CompaerPointLess> number = { */
    /* set<Point, std::greater<Point>> number = { */
    set<Point, CompaerPointGreater> number = {
        Point(1,2), 
        Point(1,-2), 
        Point(3,4), 
        Point(-3,4), 
        /* Point(2,5) */
    };
    display(number);
}

int main()
{   
    test02();
    return 0;
}

