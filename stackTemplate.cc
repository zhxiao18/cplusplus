#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

template<class T = int, int kSize = 20> 
class Stack{
public:
    Stack()
    :_top(-1),
    _data(new T[kSize]()){
        cout << "Stack()" << endl;
    }

    bool empty() const;

    bool full() const;

    void push(const T &data);

    void pop();

    T top() const;

    ~Stack();
private:
    int _top;
    T *_data;
};

template<class T, int kSize> 
bool Stack<T,kSize>::empty() const{
    return -1 == _top;
}

template<class T, int kSize> 
bool Stack<T,kSize>::full() const{
    return kSize == (_top + 1);
}

template<class T, int kSize> 
void Stack<T,kSize>::push(const T &data){
    if(!full()){
        _data[++_top] = data;
    }
    else{
        cout << "Stack Full." << endl;
        return;
    }
}

template<class T, int kSize> 
void Stack<T,kSize>::pop(){
    if(!empty()){
        cout << "出栈" << endl;
        --_top;
    }
    else{
        cout << "stack empty." << endl;
        return;
    }
}

template<class T, int kSize> 
T Stack<T,kSize>::top() const{
    return _data[_top];
}

template<class T, int kSize> 
Stack<T,kSize>::~Stack(){
    cout << "~Stack." <<endl;
    if(_data){
        delete [] _data;
        _data = nullptr;
    }
}

void test01(){
    Stack<int> stack;
    
    cout << "空否？" << stack.empty() << endl;
    cout << "满？" << stack.full() << endl;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);
    cout << "空否？" << stack.empty() << endl;
    cout << "满？" << stack.full() << endl;
    cout << "栈顶元素：" << stack.top() << endl;
    stack.pop();
    cout << "栈顶元素：" << stack.top() << endl;
}

int main()
{   
    test01();
    return 0;
}

