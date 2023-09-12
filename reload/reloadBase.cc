/* 编写Base类使下列代码输出为1 */

/* int i=2; */
/* int j=7; */

/* Base x(i); */
/* Base y(j); */
/* cout << (x+y == j - i) << endl; */
/* 提示：本题考查的其实就是运算符重载的知识点。 */

#include <iostream>
#include <string.h>
#include <stdio.h>

using std::cin;
using std::cout;
using std::endl;

class Base {
private:
    int value;

public:
    Base(int val) : value(val) {}

    Base operator+(const Base& other) const {
        return Base(value + other.value);
    }

    bool operator==(int num) const {
        return value == num;
    }
};

void test01(){
    int i = 2;
    int j = 5;
    Base x(i);
    Base y(j);

    cout << (x + y == j - i) << endl;
}

int main()
{   
    test01();
    return 0;
}

