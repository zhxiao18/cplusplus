#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Stack {
private:
    static const int MAX_SIZE = 100; // 栈的最大容量
    int data[MAX_SIZE]; // 存储栈元素的数组
    int topIndex; // 栈顶元素索引

public:
    Stack() {
        topIndex = -1; // 初始化栈为空
    }

    bool empty() {
        return topIndex == -1; // 栈为空时返回 true
    }

    bool full() {
        return topIndex == MAX_SIZE - 1; // 栈满时返回 true
    }

    void push(int value) {
        if (full()) {
            cout << "Stack Full." << endl;
            return;
        }

        topIndex++;
        data[topIndex] = value; // 将元素入栈
    }

    void pop() {
        if (empty()) {
            cout << "Stack Empty." << endl;
            return;
        }

        topIndex--; // 弹出栈顶元素
    }

    int top() {
        if (empty()) {
            cout << "Stack Empty" << endl;
            return -1;
        }

        return data[topIndex]; // 返回栈顶元素的值
    }
};

int main() {
    Stack stack;

    cout << "Is Stack Empty:" << (stack.empty() ? "true" : "false") << endl;

    // 入栈操作
    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Is Stack Empty:" << (stack.empty() ? "true" : "false") << endl;

    cout << "Top element:" << stack.top() << endl;

    // 出栈操作
    stack.pop();

    cout << "pop,the top：" << stack.top() << endl;

    // 入栈操作
    stack.push(40);

    cout << "Is Stack Full:" << (stack.full() ? "true" : "false") << endl;

    return 0;
}
