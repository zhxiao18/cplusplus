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
    //vector的 插入
    cout << "----------vector----------" << endl;
    vector<int> vec = {1,2,3,4,7,9,56,32};
    display(vec);
    vector<int>::iterator it1 = vec.begin();
    it1+=2;
    cout << "*it1 = " << *it1 <<endl;
    //插入方式1
    vec.insert(it1, 100);
    display(vec);
    cout << "*it1 = " << *it1 <<endl;
    /* vec.insert(it1, 200);//迭代器失效，需要先重新置位 */
    it1 = vec.begin();
    it1 +=2;
    cout << "*it1 = " << *it1 <<endl;

    //插入方式2
    vec.insert(it1, 3,10);
    display(vec);
    cout << "*it1 = " << *it1 <<endl;

    //插入方式3
    it1 = vec.begin();
    it1 +=2;
    vector<int> vec2 = {11,12,13,14};
    vec.insert(it1,vec2.begin(),vec2.end());
    display(vec);
    cout << "*it1 = " << *it1 <<endl;

    //插入方式4
    /* it1 = vec.begin(); */
    /* it1 += 2; */
    vec.insert(it1,{22,23,24,25});
    display(vec);
    it1 = vec.begin();
    it1 += 2;
    cout << "*it1 = " << *it1 <<endl;
    cout << vec.size() << "  " << vec.capacity() << endl;//清空元素
    vec.shrink_to_fit();
    cout << vec.capacity() << endl; ///收回内存
    cout << endl;

    cout << "-----------------list--------------" << endl;
    list<int> ls = {1,2,3,4,5,6,7};
    list<int>::iterator it2 = ls.begin();
    it2++;//指向的元素固定不变

    ls.insert(it2,11);
    display(ls);

    ls.insert(it2, 5, 12);
    display(ls);

    list<int> ls2 = {31,32,33};
    ls.insert(it2, ls2.begin(), ls2.end());
    display(ls);

    ls.insert(it2, {40,41,42});
    display(ls);


    ls.clear();
    display(ls);
}

int main()
{   
    test01();
    return 0;
}

