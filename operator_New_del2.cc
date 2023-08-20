//只能创建堆对象
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <memory>

using std::cin;
using std::cout;
using std::endl;
using std::shared_ptr;

class Student{
public:
    Student(int id, const char * name)
    :_id(id),
    _name(new char[strlen(name) + 1]())
    {
        cout << "Student(int, const char *)" << endl;
        strcpy(_name, name);
    }

    void print(){
        cout << "id: " << _id << endl << "name: " << _name << endl;
    }

    static void* operator new(size_t size){
        cout << "operator new" << endl;
        void * psize = malloc(size);
        return psize;
    }

    static void operator delete(void *ptr){
        cout << "operator delete" << endl;
        free(ptr);
    }
private:
    ~Student(){
        cout << "~Student()" << endl;
        if(_name){
            delete [] _name;
            _name = nullptr;
        }
    }
private:
    int _id;
    char * _name;
};

void test01(){
    //智能指针
    shared_ptr<Student> stu(new Student(1,"xiaoming"));
    stu->print();

    /* Student stu2(2,"xiaoming"); */ //error
}

int main()
{   
    test01();
    return 0;
}

