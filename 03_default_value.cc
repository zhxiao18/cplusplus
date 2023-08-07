#include <iostream>

using std::cin;
using std::cout;
using std::endl;

inline int add(int x = 10, int y = 8){
    cout << "x + y = " << x+y << endl;
}

int main()
{
    add(0);

    return 0;
}

