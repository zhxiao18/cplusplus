#include <iostream>
#include <string>

using std::string;
using std::isspace;
using std::isdigit;
using std::cout;
using std::cin;
using std::endl;

bool isNumeric(const string& str) {
    if (str.empty()) {
        return false;
    }

    // 去除前导空格
    size_t i = 0;
    while (i < str.length() && isspace(str[i])) {
        i++;
    }

    // 检查符号位
    if (str[i] == '+' || str[i] == '-') {
        i++;
    }

    // 判断是否出现数字
    bool hasDigits = false;

    // 处理整数部分
    while (i < str.length() && isdigit(str[i])) {
        i++;
        hasDigits = true;
    }

    // 处理小数部分
    if (i < str.length() && str[i] == '.') {
        i++;

        // 判断小数点后是否有数字
        while (i < str.length() && isdigit(str[i])) {
            i++;
            hasDigits = true;
        }
    }

    // 判断是否出现指数部分
    if (hasDigits && i < str.length() && (str[i] == 'e' || str[i] == 'E')) {
        i++;

        // 判断指数部分的符号位
        if (str[i] == '+' || str[i] == '-') {
            i++;
        }

        // 判断指数部分是否有数字
        bool hasExponentDigits = false;
        while (i < str.length() && isdigit(str[i])) {
            i++;
            hasExponentDigits = true;
        }

        // 指数部分必须有数字
        if (!hasExponentDigits) {
            return false;
        }
    }

    // 去除尾部空格
    while (i < str.length() && isspace(str[i])) {
        i++;
    }

    // 判断是否完全匹配并到达字符串末尾
    return hasDigits && i == str.length();
}

int main() {
    string input;
    cout << "请输入一个字符串: ";
    getline(cin, input);

    if (isNumeric(input)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }

    return 0;
}
