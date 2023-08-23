//序列式容器的插入
#include <iostream>
#include <vector>
#include <deque>
#include <list>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::list;

//遍历数据
template<class container >
void display(container & con){
    for(auto & elem : con){
        cout << elem << " ";
    }
    cout << endl;
}

void test01(){
    list<int> ls = {1,3,4,54,23,12,21,1,3,23};
    display(ls);
    list<int>::iterator it = ls.begin();//指向的元素固定不变

    //list的逆置
    ls.reverse();
    display(ls);

    //list排序
    ls.sort();
    display(ls);
    ls.unique();
    display(ls);
}

int main()
{   
    test01();
    return 0;
}

