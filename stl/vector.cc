#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::ifstream;
using std::vector;

template<class Container>
void print(const Container & con){
    for(auto & elem : con){
        cout << elem << " ";
    }
    cout << endl;
    cout << " ||> capacity: " << con.capacity()<< " | size: " << con.size() << endl << endl;
}

void test01(){
    // - - -- - - - - 初始化--——-- - - - - -- 
    //init 1
    vector<int> vec1;
    //init 2
    vector<int> vec2(5,2);
    //init 3
    vector<int> vecTmp(4,9);
    vector<int> vec3(vecTmp.begin(), vecTmp.end());
    //init 4
    vector<int> vec4(vecTmp);
    vector<int> vec5({4,5,6,7,8,9});
    //init 5
    vector<int> vec6 = {1,2,3,4,5,6,7,8,9};
cout << "- - - -- - - - - 遍历- - - - - -- - - -- - - - - -" << endl;

    //print 1
    for(int idx = 0; idx != vec5.size(); ++idx){
        cout << vec5[idx] << " ";
    }
    cout << endl;

    //print 2
    vector<int>::iterator it1;
    for(it1 = vec6.begin(); it1 != vec6.end(); ++it1){
        cout << *it1 << " ";
    }
    cout << endl;

    //print 3
    for(auto & elem : vec3){
        cout << elem << " ";
    }
    cout << endl;

    cout << "- - - -- - -- 尾部插入- - - --  - - - -- - - " << endl;
    print(vec5);
    cout << "push_back: ";
    vec5.push_back(3);
    print(vec5);
    cout << "push_back: ";
    vec5.push_back(10);
    print(vec5);

    cout << "- - - -- - -- 尾部删除- - - --  - - - -- - - " << endl;
    print(vec5);
    vec5.pop_back();
    cout << "tail delete: ";
    print(vec5);

    //不支持在头部插入删除
    
    cout << " ------在任意位置插入-------" << endl;

    vector<int>::iterator it4 = vec5.begin();
    ++it4;
    //找一个位置插入
    cout << "insert: ";
    vec5.insert(it4, 11);
    print(vec5);

    //插入count个相同元素
    cout << "insert: ";
    vec5.insert(it4, 4,22); //插入4个22
    print(vec5);

    //插入迭代器范围的
    vecTmp = {33,44,55,66,77};
    cout << "insert: ";
    vec5.insert(it4, vecTmp.begin(), vecTmp.end());
    print(vec5);

    //插入一个大括号的
    it4 = vec5.begin(); //迭代器失效
    cout << "insert: ";
    vec5.insert(it4, {101,102,103});
    print(vec5);

    cout << "------------删除连续重复元素22-----------"  << endl;
    print(vec5);
    for(auto it = vec5.begin(); it != vec5.end();){
        if( 22 == *it){
            vec5.erase(it);
        }else{
            ++it; //注意++时间
        }
    }
    print(vec5);

    cout << "-----交换容器内容---------" << endl;
    print(vec5);
    vector<int> vec7 = {0,0,0,0,0,0,0,0,0};
    vec5.swap(vec7);
    cout << "交换后： " << endl;
    print(vec5);

    cout << "-------清空元素----------" << endl;
    vec5.clear();
    print(vec5);

    cout << "------回收空间----------" << endl;
    vec5.shrink_to_fit();
    print(vec5);
}

int main()
{   
    test01();
    return 0;
}

