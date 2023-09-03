#pragma once

class NonCopyable
{
private:
    NonCopyable() = default;
    ~NonCopyable() = default;

    NonCopyable(const NonCopyable & rhs) = delete;
    NonCopyable & operator=(const NonCopyable & rhs) = delete;
};
