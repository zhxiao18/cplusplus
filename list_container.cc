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
    /* cout << "container 元素： "; */
    for(auto & elem : con){
        cout << elem << " ";
    }
    cout << endl;
}

void test01(){
    cout << "-----------初始化--------------" << endl;
    list<int> ls = {1,3,4,54,23,12,21,1,3,23};
    display(ls);
    list<int>::iterator it = ls.begin();//指向的元素固定不变

    cout << "--------------reverse----------------" << endl;
    //list的逆置
    ls.reverse();
    display(ls);

    cout << "-------------------sort------------------" << endl;
    //list排序
    ls.sort();  //默认按照从小到大排序
    display(ls);

    //指明按照 从小到大 进行排序
    /* ls.sort(std::less<int>()); */
    /* display(ls); */

    //指明按照从大到小排序
    /* ls.sort(std::greater<int>()); */
    /* display(ls); */
    cout << "--------unipue--------------" << endl;
    ls.unique();
    display(ls);
    
    cout << "---------------merge--------------" << endl;
    list<int> ls2 = {22,11,66,45,32,2};
    ls2.sort();
    cout << "ls2: "; 
    display(ls2);
    ls.merge(ls2);
    cout << "ls: "; 
    display(ls);
    cout << "ls2: "; 
    display(ls2); //null

    cout << "-------------splice---------" << endl;
    list<int> ls3 = {43,12,97,48,69,85};
    list<int>::iterator it2 = ls.begin();
    
    //1、把ls3所有元素 剪切 到ls中
    /* ls.splice(it2,ls3); */
    /* display(ls); */    
    /* display(ls3);   //null */

    //2、把 ls3 的指定元素 剪切 到 ls中
    auto it3 = ls3.begin();
    cout << "ls3: "; 
    display(ls3);
    ls.splice(it2,ls3,it3);
    cout << "ls: ";
    display(ls);
    cout << "ls3: ";
    display(ls3);

    //3、剪切迭代器范围的
}

int main()
{   
    test01();
    return 0;
}

