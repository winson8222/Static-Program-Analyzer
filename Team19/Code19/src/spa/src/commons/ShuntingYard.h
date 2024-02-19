#pragma once

#include <string>

class ShuntingYard {
public:
  std::string convertToPostfix(const std::string& infixExpression);
private:
  static int precedence(char c);
  static bool isOperator(char c);
  static bool isOperand(char c);
  static bool isLeftParenthesis(char c);
  static bool isRightParenthesis(char c);
  static std::string infixToPostfix(const std::string& infixExpression);
};