#include "Line.hpp"

class Line::LinePimpl{
public:
    LinePimpl(int ix1, int iy1, int ix2, int iy2)
    :_pt1(ix1, iy1),
     _pt2(ix2, iy2)
    {
        cout << "LinePimpl(int, int, int, int)" << endl;
    }

    void printLinePimpl() const{
        _pt1.print();
        cout << "=>";
        _pt2.print();
        cout << endl;
    }

    ~LinePimpl(){
        cout << "~LinePimpl" << endl;
    }

private:
     class Point{
     public:
         Point(int ix = 0, int iy = 0)
         :_ix(ix),
         _iy(iy)
         {
             cout << "Point(int,int)" << endl;
         }
         void print() const{
             cout << "(" << _ix << "," << _iy << ")";
         }

         ~Point(){
             cout << "~Point" << endl;
         }
     private:
        int _ix;
        int _iy;
     };
private:
    Point _pt1;
    Point _pt2;
};

Line::Line(int ix1, int iy1, int ix2, int iy2)
:_linePimpl(new LinePimpl(ix1, iy1, ix2, iy2))
{
    cout << "Line(int, int, int, int)" << endl;
} 

void Line::printLine() const{
    _linePimpl->printLinePimpl();
}

Line::~Line(){
    cout << "~Line" << endl;
    if(_linePimpl){
        delete _linePimpl;
        _linePimpl = nullptr;
    }
}
