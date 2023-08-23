#ifndef __LINE_H__
#define __LINE_H__

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::ostream;

class Line{
public:
    Line(int ix1, int iy1, int ix2, int iy2);
    void printLine() const;
    ~Line();
private:
    class LinePimpl; //类声明
    LinePimpl * _linePimpl;
};

#endif
