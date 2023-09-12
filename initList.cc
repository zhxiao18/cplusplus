#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class Point{
public:
    Point(int x, int y)
    :_px(x)
    ,_py(y)
    {
        cout << "Point init" << endl;       
    }

    void print(){
        cout << "(" << _px << "," << _py << ")" << endl;
    }
private:
    int _px;
    int _py;
};

int main()
{
    Point p(2,3);
    p.print();
    return 0;
}

