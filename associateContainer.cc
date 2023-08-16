#include <iostream>
#include <set>
#include <utility>

using std::cout;
using std::endl;
using std::set;
using std::pair;

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

    //2、auto
    for(auto &elem : number){
        cout << elem << " ";
    }
    cout << endl;

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

    cout << "------------insert--------------" << endl;
    /* auto ret = number.insert(8); */  //等价
    pair<set<int>::iterator,bool> ret = number.insert(12);
    if(ret.second){
        cout << "该元素插入成功：" << *ret.first << endl;
    }else{
        cout << "insert error" << endl;
    }
    auto it3 = number.begin();
    *it3 = 100;
}

int main()
{   
    test01();
    return 0;
}

