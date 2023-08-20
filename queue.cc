//队列的实现(循环队列)
#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Queue{
public:
    Queue(size_t size = 10)
    :_front(0),
    _rail(0),
    _size(size),
    _data(new int[_size]())
    {
        cout << "Queue(size_t size = 10)" << endl;
    }
    
    bool full() const{
        return (_front == (_rail +1) % _size);
    }    

    bool empty() const{
        return _front == _rail;
    }

    void enQueue(const int & val){
        if(full()){
            cout << "Queue Full." << endl;
            return;
        }
        _data[_rail++] = val;
        _rail %= _size;
        /* return 1; */
    }

    void deQueue(){
        if(empty()){
            cout << "Queue Empty" << endl;
            return;
        }
        ++_front;
        _front %= _size;
    }

    int getFront() const{
        return _data[_front];
    }

    int getRail() const{
        return _data[(_rail - 1 + _size) % _size];
    }

    ~Queue(){
        if(_data){
            delete [] _data;
            _data = nullptr;
        }
    }
private:
    int _front; //队头
    int _rail;  //队尾
    int _size;
    int * _data; //队列数组
};

void test01(){
    Queue queue;
    cout << "Queue full?" << queue.full() << endl;
    cout << "Queue empty?" << queue.empty() << endl;

    for(int i = 0; i < 9; ++i){
        queue.enQueue(i);
    }
    cout << "Queue full?" << queue.full() << endl;
    cout << "Queue empty?" << queue.empty() << endl;
    
    for(int idx = 0; idx < 10; ++idx){
        cout << queue.getFront() << "";
        queue.deQueue();
    }
    cout << endl;
}

int main()
{   
    test01();
    return 0;
}

