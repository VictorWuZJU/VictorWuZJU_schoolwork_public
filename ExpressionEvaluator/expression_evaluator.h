#ifndef STACK
#define STACK

#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <stdexcept>

// 检查括号配对
bool bracket_paring(std::string &expression) {
    std::stack<char> bracket_check; // 存放括号
    char right_bracket;
    for (char c : expression) {
        if (c == '(' || c == '[' || c == '{') {
            bracket_check.push(c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (bracket_check.empty()) {
                std::cout << "Bracket Paring error" << std::endl;
                return false;
            } else {
                right_bracket = bracket_check.top();
                bracket_check.pop();
                if ((right_bracket == '(' && c != ')') ||
                    (right_bracket == '[' && c != ']') ||
                    (right_bracket == '{' && c != '}')) {
                    std::cout << "Bracket Paring Error!" << std::endl;
                    return false;
                }
            }
        }
    }
    if (!bracket_check.empty()) {
        std::cout << "Bracket Paring Error" << std::endl;
        return false;
    }
    return true;
}

bool isOperator(char digit) {
    return (digit == '+' || digit == '-' || digit == '*' || digit == '/');
}

// 检查四则运算符（+，-，*，/）是否有两次及以上的连续使用
bool Continuous_usage_of_Symbols(std::string &expression) {
    if (expression.size() < 2) return true; // 长度小于2的表达式直接返回true
    for (size_t i = 0; i < expression.size() - 1; ++i) {
        if (isOperator(expression[i]) && isOperator(expression[i + 1])) {
            std::cout << "Continuous usage of symbols error!" << std::endl;
            return false;
        }
    }
    return true;
}

// 返回运算符的优先级
int priority(char digit) {
    if (digit == '+' || digit == '-') return 1;
    if (digit == '*' || digit == '/') return 2;
    return 0;
}

// 执行运算
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        default: return 0;
    }
}

// 判断是否为括号
bool isBracket(char digit) {
    return (digit == '(' || digit == ')' || digit == '[' || digit == ']' || digit == '{' || digit == '}');
}

// 判断是否为右括号
bool isRightBracket(char digit) {
    return (digit == ')' || digit == ']' || digit == '}');
}

// 判断是否为左括号
bool isLeftBracket(char digit) {
    return (digit == '(' || digit == '[' || digit == '{');
}

std::vector<std::string> Infix_to_Postfix(std::string expression) {
    std::stack<char> symbols_container;
    std::vector<std::string> postfix;
    bool hasDecimalPoint = false; // 用于标记是否包含小数点

    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];
        if (isspace(c)) continue; // 忽略空格
        if (isdigit(c) || c == '.') {
            std::string num;
            // 读取数字和小数点
            while (i < expression.size() && (isdigit(expression[i]) || expression[i] == '.')) {
                if (expression[i] == '.') {
                    if (hasDecimalPoint) break; // 如果已经有过小数点，则不再读取
                    hasDecimalPoint = true;
                }
                num += expression[i++];
            }
            --i; // 因为循环中的递增，需要递减i以匹配循环的递增
            postfix.push_back(num);
            hasDecimalPoint = false; // 重置标记
        } else if (isLeftBracket(c)) {
            symbols_container.push(c);
        } else if (isRightBracket(c)) {
            while (!symbols_container.empty() && isLeftBracket(symbols_container.top())) {
                postfix.push_back(std::string(1, symbols_container.top()));
                symbols_container.pop();
            }
            if (!symbols_container.empty() && isLeftBracket(symbols_container.top())) {
                symbols_container.pop();
            }
        } else if (isOperator(c)) {
            while (!symbols_container.empty() && priority(symbols_container.top()) >= priority(c)) {
                postfix.push_back(std::string(1, symbols_container.top()));
                symbols_container.pop();
            }
            symbols_container.push(c);
        }
    }

    while (!symbols_container.empty()) {
        postfix.push_back(std::string(1, symbols_container.top()));
        symbols_container.pop();
    }

    return postfix;
}

// 计算后缀表达式的值
double evaluatePostfix(const std::vector<std::string>& postfix) {
    std::stack<double> values;

    for (const std::string& token : postfix) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '.')) {
            values.push(std::stod(token)); // 将数字转换为double并压入栈中
        } else if (isOperator(token[0])) {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            double result = applyOp(a, b, token[0]);
            values.push(result);
        }
    }

    return values.top(); // 返回栈顶的值，即结果
}

// 总体算式合法性的检查
bool valid_check(const std::string &expression) {
    return bracket_paring(const_cast<std::string&>(expression)) && Continuous_usage_of_Symbols(const_cast<std::string&>(expression));
}

#endif