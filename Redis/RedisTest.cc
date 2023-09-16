#include <iostream>
#include <hiredis/hiredis.h>
#include <vector>

using namespace std;

class MyRedis
{
public:
    MyRedis()
    {
    }

    ~MyRedis()
    {
        _redisConn = nullptr;
        _redisReply = nullptr;
    }

    void Connect(const string ip, unsigned short port)
    {
        _redisConn = redisConnect(ip.c_str(), port);
        if (_redisConn != nullptr && _redisConn->err)
        {
            cerr << "redisConnect:" << _redisConn->errstr << endl;
        }
    }

    vector<string> getVal(const string key)
    {
        _redisReply = (redisReply *)redisCommand(_redisConn, "smembers %s", key.c_str());
        // _redisReply = (redisReply *)redisCommand(_redisConn, "get %s", key.c_str());
        vector<string> ret;
        if (REDIS_REPLY_NIL == _redisReply->type)
        {
            cout << "无所查找的关键词" << endl;
            return ret;
        }
        for (size_t i = 0; i < _redisReply->elements; ++i)
        {
            cout << _redisReply->element[i]->str << endl;
            ret.push_back(_redisReply->element[i]->str);
        }

        freeReplyObject(_redisReply);
        _redisReply = nullptr;
        return ret;
    }

    // void getVal(const string key, string &retStr)
    // {
    //      _redisReply = (redisReply *)redisCommand(_redisConn, "smembers %s", key.c_str());
    //     _redisReply = (redisReply *)redisCommand(_redisConn, "get %s", key.c_str());
    //     if (REDIS_REPLY_NIL == _redisReply->type)
    //     {
    //         cout << "无所查找的关键词" << endl;
    //         return;
    //     }

    //     retStr = _redisReply->str;
    //     cout << retStr << endl;

    //     freeReplyObject(_redisReply);
    //     _redisReply = nullptr;
    // }

    void setVal(const string key, const string value)
    {
        _redisReply = (redisReply *)redisCommand(_redisConn, "sadd %s %s", key.c_str(), value.c_str());
        freeReplyObject(_redisReply);
        _redisReply = nullptr;
    }

private:
    redisContext *_redisConn;
    redisReply *_redisReply;
};

int main(void)
{
    MyRedis my_redis;
    my_redis.Connect("0.0.0.0", 6379);
    string str = "111111111111111111";
    string str2 = "22222222222222222222";

    my_redis.setVal("testkey", str);
    my_redis.setVal("testkey", str2);

    vector<string> ret = my_redis.getVal("习近平");
    for (auto &elem : ret)
    {
        cout << elem << " ";
    }
    cout << endl;
    cout << ret.size() << endl;
    // cout << str << endl;
}