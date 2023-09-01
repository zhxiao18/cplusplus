//给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
//有效字符串需满足：
//左括号必须用相同类型的右括号闭合。
//左括号必须以正确的顺序闭合。
//每个右括号都有一个对应的相同类型的左括号。
#include <iostream>
#include <stack>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::string;

class Bracket
{
public:
    bool isValid(string s)
    {
        stack<char> stk;
        for(char elem : s)
        {
            if(isOpenBracket(elem))
            {
                stk.push(elem);
            }
            else if(isCloseBracket(elem))//是闭括号
            {
                if(stk.empty() || !isMatchBracket(stk.top(), elem))
                {
                    return false;
                }
                stk.pop();
            }
        }
        return stk.empty();
    }
private:
    bool isOpenBracket(char c)
    {
        return c == '[' || c == '{' || c == '(';
    }

    bool isCloseBracket(char c)
    {
        return c == ']' || c == '}' || c == ')';
    }

    bool isMatchBracket(char top, char elem)
    {
        return (top == '[' && elem == ']') ||
            (top == '{' && elem == '}') || 
            (top == '(' && elem == ')');
    }
};

int main(int argc, char * argv[])
{   
    Bracket brack;
    bool ret = brack.isValid("(){}[]");

    if(ret){
        cout <<" is valid." << endl; 
    }
    else
    {
        cout << " is not valid." << endl;
    }
    return 0;
}

