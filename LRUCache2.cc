#include <iostream>
// #include <vector>
#include <list>
#include <map>
#include <unordered_map>

using namespace std;

class LRUCache
{
public:
    LRUCache(int capacity)
        : _capacity(capacity)
    {
    }

    ~LRUCache() {}

    void put(int key, int val)
    {
        unordered_map<int, list<CacheNode>::iterator>::iterator it;
        if ((it = _cache.find(key)) != _cache.end()) // key已经存在
        {
            // 更新数据，并把结点移到链表最前面
            it->second->_value = val;
            _nodes.splice(_nodes.begin(), _nodes, it->second);
        }
        else
        {
            // key不存在
            // 添加结点，如果容量不够，删除结尾结点
            CacheNode newNode(key, val);
            if (_capacity == _nodes.size()) // 链表满
            {
                auto &delNode = _nodes.back();
                _cache.erase(delNode._key);
                _nodes.pop_back();
            }
            _nodes.push_front(newNode);
            _cache.insert(make_pair(key, _nodes.begin()));
        }
    }

    // 查找key
    int get(int key)
    {
        auto it = _cache.find(key);
        // 没找到
        if (it == _cache.end())
        {
            return -1;
        }
        else
        {
            _nodes.splice(_nodes.begin(), _nodes, it->second);
            return it->second->_value;
        }
    }

private:
    struct CacheNode
    {
        CacheNode(int k, int v)
            : _key(k),
              _value(v)
        {
        }

        int _key;
        int _value;
    };

private:
    int _capacity;
    list<CacheNode> _nodes;
    unordered_map<int, list<CacheNode>::iterator> _cache;
};

int main(int argc, char *argv[])
{
    LRUCache lcache(2);

    int ret = lcache.get(1);
    cout << "get(1) = " << ret << endl;

    lcache.put(1, 2);
    ret = lcache.get(1);
    cout << "get(1) = " << ret << endl;

    lcache.put(2, 3);
    ret = lcache.get(2);
    cout << "get(2) = " << ret << endl;

    lcache.put(3, 6);
    ret = lcache.get(1);
    cout << "get(1) = " << ret << endl;
    ret = lcache.get(2);
    cout << "get(2) = " << ret << endl;

    ret = lcache.get(3);
    cout << "get(3) = " << ret << endl;
    return 0;
}