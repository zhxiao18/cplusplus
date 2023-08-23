//队列的模板形式
#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

template<class T, size_t kSize = 10>
class Queue{
public:
    Queue()
    :_front(0),
    _rear(0),
    _data(new T[kSize])
    {
        cout << "Queue()" << endl;
    }

    bool empty();

    bool full();

    void enQueue(const T & val);

    void deQueue();

    T getFront();

    T getRear();

    ~Queue();
private:
    int _front;
    int _rear;
    T *_data;
};

template<class T, size_t kSize>
bool Queue<T, kSize>::empty(){
    return _front == _rear;
}

template<class T, size_t kSize>
bool Queue<T, kSize>::full(){
    return (_front == (_rear + 1) % kSize);
}

template<class T, size_t kSize>
void Queue<T, kSize>::enQueue(const T & val){
    if(!full()){
        _data[_rear++] = val;
        _rear %= kSize;
    }
    else{
        cout << "Queue Full." << endl;
    }
}

template<class T, size_t kSize>
void Queue<T, kSize>::deQueue(){
    if(empty()){
        cout << "Queue Empty." <<endl;
    }
    ++_front;
    _front %= kSize;
}

template<class T, size_t kSize>
T Queue<T, kSize>::getFront(){
    if(!empty()){
        return _data[_front];
    }
    else{
        cout << "Queue Empty." <<endl;
        return -1;
    }
}

template<class T, size_t kSize>
T Queue<T, kSize>::getRear(){
    if(!empty()){
        //特别注意
        return _data[(_rear - 1 + kSize) % kSize];
    }
    else{
        cout << "Queue Empty." <<endl;
        return -1;
    }
}

template<class T, size_t kSize>
Queue<T, kSize>::~Queue(){
    cout << "~Queue()." << endl;
    if(_data){
        delete [] _data;
        _data = nullptr;
    }
}

void test01(){
    Queue<int> queue;
    cout << "Empty? " << queue.empty() << endl;
    cout << "Full? " << queue.full() << endl;
    cout << "-------------------------" << endl;
    queue.enQueue(1);
    cout << "getFront: " << queue.getFront() << endl;
    cout << "getRear: " << queue.getRear() << endl;
    queue.enQueue(2);
    queue.enQueue(3);
    queue.enQueue(4);
    queue.enQueue(5);
    queue.enQueue(6);
    cout << "Empty? " << queue.empty() << endl;
    cout << "Full? " << queue.full() << endl;
    cout << "-------------------------" << endl;
    cout << "getFront: " << queue.getFront() << endl;
    cout << "getRear: " << queue.getRear() << endl;
    queue.deQueue();
    queue.deQueue();
    cout << "getFront: " << queue.getFront() << endl;
    cout << "getRear: " << queue.getRear() << endl;
}

int main()
{   
    test01();
    return 0;
}

