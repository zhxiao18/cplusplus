#include <iostream>
#include <memory>
#include <algorithm>
#include <iterator>

using std::cin;
using std::cout;
using std::endl;
using std::allocator;
using std::copy;
using std::ostream_iterator;

template<typename T> 
class Vector 
{ 
public:
    using iterator = T *;

    Vector();     
    ~Vector();          
    //在头部添加元素
    void push_back(const T & value);      
    //在头部删除元素
    void pop_back();         
    int size() const;     
    int capacity() const; 
    iterator begin(){
        return _start;
    }
    iterator end(){
        return _finish;
    }

private:     
    void reallocate();//重新分配内存,动态扩容要用的 
private:         
    static std::allocator<T> _alloc;          
    T *_start;                 //指向数组中的第一个元素     
    T *_finish;            //指向最后一个实际元素之后的那个元素     
    T *_end_of_storage;        //指向数组本身之后的位置 
};
template<typename T>
std::allocator<T> Vector<T>::_alloc;          

template<typename T>
Vector<T>::Vector()
:_start(nullptr),
_finish(nullptr),
_end_of_storage(nullptr)
{
}     

template<typename T>
Vector<T>::~Vector(){
    if(_start){
        while(_finish != _start){
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start, capacity());
    }    
}   

template<typename T>
void Vector<T>::push_back(const T & value){
    //判满
    if(size() == capacity()){
        reallocate();
    }
    if(size() < capacity()){ 
        _alloc.construct(_finish++, value);
    }
}   

template<typename T>
void Vector<T>::pop_back(){
    //判空
    if(size() > 0){
        _alloc.destroy(--_finish);
    }
}   

template<typename T>
int Vector<T>::size() const{
    return _finish - _start;
}   

template<typename T>
int Vector<T>::capacity() const{
    return _end_of_storage - _start;
}

template<typename T>
void Vector<T>::reallocate()//重新分配内存,动态扩容要用的 
{
    //1、申请两倍空间
    int oldCapacity = capacity();
    int newCapacity = oldCapacity > 0 ? 2 * oldCapacity : 1;

    T * ptmp = _alloc.allocate(newCapacity);

    //2、把旧空间的数据复制到新空间
    if(_start)//如果不是第一次插入，复制数据
    {
        std::uninitialized_copy(_start, _finish, ptmp);

        //3、释放旧空间
        while(_start != _finish){
            //将旧空间元素全部销毁
            _alloc.destroy(--_finish);
        }
        _alloc.deallocate(_start, capacity());
    }

    //4、让指针指向新空间
    _start = ptmp;
    _finish = _start + oldCapacity;
    _end_of_storage = _start + newCapacity;
}


void printCapacity(const Vector<int> & con){
    cout << "size = " << con.size() << endl;
    cout << "capacity = " << con.capacity() << endl;
}

void test01(){
    Vector<int> vec;
    printCapacity(vec);

    cout << endl;
    vec.push_back(1);
    printCapacity(vec);

    cout << endl;
    vec.push_back(2);
    printCapacity(vec);

    cout << endl;
    vec.push_back(3);
    printCapacity(vec);

    //遍历
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    vec.pop_back();
    copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

int main()
{   
    test01();
    return 0;
}

