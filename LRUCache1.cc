#include <time.h>
#include <unistd.h>
#include <iostream>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::map;

struct member{
    member() = default;
    member(int val)
    :_val(val),
    _nowTime(time(NULL))
    {
        /* cout << "member(int,time_t)" << endl; */
    }
        
    ~member(){
        /* cout << "~member()" << endl; */
    }

    int _val;
    time_t _nowTime;
};

class LURCache{
public:
    LURCache(size_t capacity,  size_t times = 0, size_t maxTimes = 2*105)
    :_capacity(capacity),
    _times(times),
    _maxTimes(maxTimes)
    {
        cout << "LURCache(size_t capacity,  size_t times = 0)" << endl;
    }
    
    int getSize(){
         return _data.size();
    }

    int getLastActive(){
        map<int,member>::iterator it = _data.begin();
        for(auto it2 = it; it2 != _data.end(); ++it2){
            /* cout << it2->second._nowTime << endl; */
            if(it2->second._nowTime < it->second._nowTime){
                it = it2;
            }
        }
        return it->first; 
    }

    int get(int key){
        if(_times > _maxTimes){
            cout << "too many get/put" << endl;
            return 0;
        }
        auto it = _data.find(key);
        if(it == _data.end()){
            return -1;
        }else{
            ++_times;
            _data[key]._nowTime = time(NULL);
            return _data[key]._val;
        }
    }

    void put(int key, int value){
        if(_times > _maxTimes){
            cout << "too many get/put" << endl;
            return;
        }
            
        if(_data.count(key) != 0){
            _data[key]._val = value;
            _data[key]._nowTime = time(NULL);
        }
        else
        {
            if(_capacity == _data.size()){
                int delKey = getLastActive();
                _data.erase(_data.find(delKey));
            }
            _data.insert({key,member(value)});
        }
        ++_times;
    }

    ~LURCache(){
        cout << "~LURCache()" << endl;
    }
private:
    size_t _capacity;
    map<int,member> _data;
    size_t _times;
    size_t _maxTimes;
};

void test01(){
    LURCache cache(2);
    cache.put(1,1);
    cout << cache.getSize() << endl;
    cache.put(2,2);
    cout << "get(1): " << cache.get(1) << endl;
    cout << cache.getSize() << endl;
    cache.put(3,3);
    cout << "get(2): " << cache.get(2) << endl;
    cout << "get(1): " << cache.get(1) << endl;
    cache.put(4,4);
    cout << "get(2): " << cache.get(2) << endl;
    cout << "get(3): " << cache.get(3) << endl;
    cout << "get(4): " << cache.get(4) << endl;
    sleep(1);
    cache.put(3,6);
    cache.put(5,5);
    cout << "get(3): " << cache.get(3) << endl;
    cout << "get(4): " << cache.get(4) << endl;
    cout << "get(5): " << cache.get(5) << endl;
}

int main()
{   
    test01();
    return 0;
}

