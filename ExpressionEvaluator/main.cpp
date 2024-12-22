#include "expression_evaluator.h"
#include <iostream>
#include <string>

int main() {
    // 测试表达式
    std::vector<std::string> test_expressions = {
        "(3+4)*5",       // 合法表达式
        "3++4",          // 连续运算符错误
        "(3+4",           // 括号不匹配错误
        "3+4*(2/",     // 括号不匹配错误
        "3.14+2",         // 包含小数点的合法表达式
        "(3+[4*5])"     // 包含不同类型括号的错误表达式
    };

    // 测试每种错误情况
    for (const std::string& expression : test_expressions) {
        std::cout << "Testing expression: " << expression << std::endl;
        if (!valid_check(expression)) {
            std::cout << "Invalid expression." << std::endl;
            continue; // 如果表达式不合法，跳过后续处理
        }

        std::vector<std::string> postfix = Infix_to_Postfix(expression);
        std::cout << "Postfix expression: ";
        for (const std::string& token : postfix) {
            std::cout << token << " ";
        }
        std::cout << std::endl;

        try {
            double result = evaluatePostfix(postfix);
            std::cout << "Calculated value: " << result << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    // 用户输入算式的接口
    std::string user_expression;
    std::cout << "Enter an expression to convert to postfix and calculate its value: ";
    std::getline(std::cin, user_expression);

    if (!valid_check(user_expression)) {
        std::cout << "Invalid expression." << std::endl;
    } else {
        std::vector<std::string> postfix = Infix_to_Postfix(user_expression);
        std::cout << "Postfix expression: ";
        for (const std::string& token : postfix) {
            std::cout << token << " ";
        }
        std::cout << std::endl;

        try {
            double result = evaluatePostfix(postfix);
            std::cout << "Calculated value: " << result << std::endl;
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }

    std::cout << "Press any button to continue……" << std::endl;
    std::string line;
    std::getline(std::cin, line);

    return 0;
}