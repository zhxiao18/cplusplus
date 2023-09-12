#include <iostream>
#include <deque>

using std::cin;
using std::cout;
using std::endl;
using std::deque;

template<typename Container>
void print(const Container & con){
    /* for(auto & elem : con){ */
    /*     cout << elem << " "; */
    /* } */
    /* cout << endl; */

    for(int idx = 0; idx != con.size(); idx++){
        cout << con[idx] << " ";
    }
    cout << endl;
    cout << "||> size: " << con.size() << endl;
}

void test01(){
    /* deque<int> dq1; */
    /* deque<int> dq(2,4); */
    // 初始化
    deque<int> dq = {1,2,3,4,5,6,7,8,9};
    print(dq);

    //尾部插入删除
    cout << "--------tail insert/delete--------" << endl;
    dq.push_back(10);
    dq.push_back(11);
    dq.push_back(12);
    print(dq);

    dq.pop_back();
    print(dq);

    cout << "--------head insert/delete--------" << endl;
    dq.push_front(22);
    dq.push_front(33);
    dq.push_front(44);
    dq.push_front(55);
    print(dq);
    dq.pop_front();
    print(dq);

    cout << "--------random insert--------" << endl;
    deque<int>::iterator it = dq.begin();
    dq.insert(it,60);
    print(dq);

    cout << "---------------clear、shrink_to_fit------------" <<endl;
    dq.clear();
    print(dq);
}

int main()
{   
    test01();
    return 0;
}

