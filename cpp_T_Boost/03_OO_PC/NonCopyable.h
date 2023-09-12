#ifndef __NONCOPYABLE_H__
#define __NONCOPYABLE_H__

//抽象类
class NonCopyable
{
/* public: */
/* private: */
protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable &rhs) = delete;
    NonCopyable &operator=(const NonCopyable &rhs) = delete;
};

#endif
