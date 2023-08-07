#include <iostream>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class Queue {
private:
    static const int MAX_SIZE = 100; // 队列的最大容量
    int data[MAX_SIZE]; // 存储队列元素的数组
    int frontIndex; // 队头元素索引
    int backIndex; // 队尾元素索引

public:
    Queue() {
        frontIndex = -1; // 初始化队列为空
        backIndex = -1;
    }

    bool empty() {
        return frontIndex == -1; // 队列为空时返回 true
    }

    bool full() {
        return (backIndex + 1) % MAX_SIZE == frontIndex; // 队列满时返回 true
    }

    void push(int value) {
        if (full()) {
            cout << "队列已满，无法执行 push 操作" << endl;
            return;
        }

        if (empty()) {
            frontIndex = 0; // 第一个元素入队时更新队头索引
        }

        backIndex = (backIndex + 1) % MAX_SIZE;
        data[backIndex] = value; // 将元素入队
    }

    void pop() {
        if (empty()) {
            cout << "队列为空，无法执行 pop 操作" << endl;
            return;
        }

        if (frontIndex == backIndex) {
            frontIndex = -1; // 最后一个元素出队时更新队头索引
            backIndex = -1;
        } else {
            frontIndex = (frontIndex + 1) % MAX_SIZE; // 出队后更新队头索引
        }
    }

    int front() {
        if (empty()) {
            cout << "队列为空，无法获取队头元素" << endl;
            return -1;
        }

        return data[frontIndex]; // 返回队头元素的值
    }

    int back() {
        if (empty()) {
            cout << "队列为空，无法获取队尾元素" << endl;
            return -1;
        }

        return data[backIndex]; // 返回队尾元素的值
    }
};

int main() {
    Queue queue;

    cout << "队列是否为空：" << (queue.empty() ? "是" : "否") << endl;

    // 入队操作
    queue.push(10);
    queue.push(20);
    queue.push(30);

    cout << "队列是否为空：" << (queue.empty() ? "是" : "否") << endl;

    cout << "队头元素：" << queue.front() <<endl;
    cout << "队尾元素：" << queue.back() << endl;

    // 出队操作
    queue.pop();

    cout << "队头元素：" << queue.front() << endl;
    cout << "队尾元素：" << queue.back() << endl;

    // 入队操作
    queue.push(40);

    cout << "队列是否已满：" << (queue.full() ? "是" : "否") << endl;

    return 0;
}
