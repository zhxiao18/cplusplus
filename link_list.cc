#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

struct Node{
    Node(int data = 0, Node *pre = nullptr, Node * next = nullptr)
    :_data(data),
    _pre(pre),
    _next(next)
    {
        cout << "Node(int, Node *, Node *)" << endl;
    }

    ~Node(){
        cout << "~Node()" << endl;
    }
    int _data;
    Node *_pre;
    Node *_next;
};

class List{
public:
    List()
    :_head(new Node()),
    _rear(new Node()),
    _size(0)
    {
        cout << "List()" << endl;
        _head->_next = _rear;
        _rear->_next = _head;
    }

    ~List(){
        cout << "~List" << endl;
        Node * delNode = _head->_next;
        while(delNode){
            Node *next = delNode->_next;
            delete delNode;
            delNode = nullptr;
            delNode = next;
            _size--;
        }
        delete _head;
        _head = nullptr;
    }

    void push_front(int data)//在头部进行插入
    {
        //创建新节点
        Node *newNode = new Node();
        newNode->_data = data;
        newNode->_pre = _head;
        newNode->_next = _head->_next;
        _head->_next->_pre = newNode;
        _head->_next = newNode;

        ++_size;
    }

    void push_back(int data);//在尾部进行插入
    

    void pop_front(){//在链表头部进行删除
        
    }

    void pop_back();//在链表的尾部进行删除

    bool find(int data);//在链表中进行查找

    void insert(int pos, int data);//在指定位置后面插入pos

    void display() const //打印链表
    {
        if(_size == 0){
            cout << "链表为空，无法打印" << endl;
            return;
        }
        Node * tmp = _head->_next;
        while(tmp && tmp != _rear){
            cout << tmp->_data << "->";
            tmp = tmp ->_next;
        }
        cout << endl;
    }

    void erase(int data);//删除一个指定的节点	
private:
    Node *_head;
    Node *_rear;
    int _size;
}

void test01(){

}

int main()
{   
    test01();
    return 0;
}

