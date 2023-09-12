#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <memory>

using std::cout;
using std::endl;
using std::list;
using std::find;
using std::string;
using std::unique_ptr;

class Observer;//前向声明

class Subject
{
public:
    //添加
    virtual void attach(Observer *pObserver) = 0;
    //删除
    virtual void detach(Observer *pObserver) = 0;
    //发通知(微博更新)
    virtual void notify() = 0;

    virtual ~Subject() {}
};

class ConcreteSubject
: public Subject
{
public:
    void attach(Observer *pObserver) override;
    void detach(Observer *pObserver) override; 
    void notify() override;

    void setStatus(int status)
    {
        _status = status;
    }

    int getStatus() const
    {
        return _status;
    }

private:
    list<Observer *> _obList;
    int _status;
};

class Observer
{
public:
    virtual void update(int) = 0;
    virtual ~Observer() { }
};

class ConcreteObserverA
: public Observer
{
public:
    ConcreteObserverA(const string &name)
    : _name(name)
    {

    }
    void update(int value) 
    {
        cout << "ConcreteObserverA " << _name << ", value = " << value << endl;
    }

private:
    string _name;

};

class ConcreteObserverB
: public Observer
{
public:
    ConcreteObserverB(const string &name)
    : _name(name)
    {

    }
    void update(int value) 
    {
        cout << "ConcreteObserverB " << _name << ", value = " << value << endl;
    }

private:
    string _name;

};

void ConcreteSubject::attach(Observer *pObserver) 
{
    if(pObserver)
    {
        //注册到具体主题上来
        _obList.push_back(pObserver);
    }
}

void ConcreteSubject::detach(Observer *pObserver) 
{
    for(auto it = _obList.begin(); it != _obList.end(); ++it)
    {
        if(*it == pObserver)
        {
            //取消关注
            _obList.remove(pObserver);
            break;
        }
    }
}

void ConcreteSubject::notify() 
{
    //遍历list，对每一个观察者都进行通知
    for(auto &ob : _obList)
    {
        ob->update(_status);//可以体现多态
    }
}

int main(int argc, char **argv)
{
    unique_ptr<ConcreteSubject> pSubject(new ConcreteSubject());
    unique_ptr<Observer> pObserverA(new ConcreteObserverA("lili"));
    unique_ptr<Observer> pObserverB(new ConcreteObserverB("lucy"));

    pSubject->setStatus(2);

    //将观察者添加到主题中（也就是关注某个论坛）
    pSubject->attach(pObserverA.get());
    pSubject->attach(pObserverB.get());

    pSubject->notify();

    cout << endl;
    pSubject->detach(pObserverB.get());
    pSubject->setStatus(3);
    pSubject->notify();

    return 0;
}
