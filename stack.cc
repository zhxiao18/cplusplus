#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Stack{
public:
    Stack(size_t size = 10)
    :_top(-1),
    _size(size),
    _data(new int[size]())
    {
        cout << "Stack(size_t size = 10)" << endl;
    }

    //判空
    bool empty() const{
        return -1 == _top;
    }

    //判满
    bool full() const{
        return ((int)_size == _top + 1);
    }    

    //入栈
    void push(const int &data){
        if(full()){
            cout << "栈满" << endl;
            return;
        }
        _data[++_top] = data;
    }

    //出栈
    int pop() {
        if(empty()){
            cout << "栈空" << endl;
            return -1;
        }
        return _data[_top--]; 
    }

    ~Stack(){
        if(_data){
            delete [] _data;
            _data = nullptr;
        }
    }
private:
    int _top;//栈顶指针
    size_t _size; //栈的大小
    int * _data;
};

void test01(){
    Stack stack;
    cout << "栈满？" << stack.full() << endl;
    cout << "栈空？" << stack.empty() << endl;;

    for(int i = 0; i < 11; ++i){
        stack.push(i);
    }
    cout << "栈满？" << stack.full() << endl;
    cout << "栈空？" << stack.empty() << endl;;
    for(int i = 0; i < 11; ++i){
        cout <<stack.pop() << " ";
    }
}
int main()
{   
    test01();
    return 0;
}
