#ifndef _NOCOPYABLE_H__
#define _NOCOPYABLE_H__

//抽像类
class NoCopyable
{
protected:
    NoCopyable() = default;
    ~NoCopyable() = default;

    NoCopyable(const NoCopyable & rhs) = delete;
    NoCopyable & operator=(const NoCopyable & rhs) = delete;
};

#endif
