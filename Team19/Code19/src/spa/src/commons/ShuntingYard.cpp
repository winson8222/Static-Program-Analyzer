#include "ShuntingYard.h"

#include <stack>

// ai-gen start(copilot, 1, e)
// prompt: used copilot
std::string ShuntingYard::convertToPostfix(const std::string& infixExpression) {
  return infixToPostfix(infixExpression);
}

int ShuntingYard::precedence(char c) {
  if (c == '+' || c == '-') {
    return 1;
  } else if (c == '*' || c == '/') {
    return 2;
  } else if (c == '^') {
    return 3;
  } else {
    return -1;
  }
}

bool ShuntingYard::isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool ShuntingYard::isOperand(char c) {
  return c >= '0' && c <= '9' || c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

bool ShuntingYard::isLeftParenthesis(char c) {
  return c == '(';
}

bool ShuntingYard::isRightParenthesis(char c) {
  return c == ')';
}

std::string ShuntingYard::infixToPostfix(const std::string& infixExpression) {
    std::string postfixExpression;
    std::stack<char> stack;
    for (char c : infixExpression) {
        if (c == ' ') {
        continue;
        }
        if (isOperand(c)) {
            postfixExpression += "'";
            postfixExpression += c;
            postfixExpression += "'";
        } else if (isOperator(c)) {
            while (!stack.empty() && isOperator(stack.top()) && ( precedence(c) <= precedence(stack.top()))) {
                postfixExpression += "'";
                postfixExpression += stack.top();
                postfixExpression += "'";
                stack.pop();
            }
            stack.push(c);
        } else if (isLeftParenthesis(c)) {
            stack.push(c);
        } else if (isRightParenthesis(c)) {
            while (!stack.empty() && !isLeftParenthesis(stack.top())) {
                postfixExpression += "'";
                postfixExpression += stack.top();
                postfixExpression += "'";
                stack.pop();
            }
            stack.pop();
        }
    }
    while (!stack.empty()) {
        postfixExpression += "'";
        postfixExpression += stack.top();
        postfixExpression += "'";
        stack.pop();
    }
    return postfixExpression;
}
// ai-gen end
