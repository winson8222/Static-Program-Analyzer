#pragma once

#include <string>
#include <stack>
#include "Shunt.h"

// ai-gen start(copilot, 0, e)
// prompt: used copilot

enum class Precedence {
    INVALID = -1,
    LOW = 1,
    HIGH = 2,
};

class ShuntingYard {
public:
  static std::string convertToPostfix(const std::string& infixExpression);
private:
    static std::string makeQuoted(char c);
    static Precedence getPrecedence(char c);
    static bool isOperator(char c);
    static bool isOperand(char c);
    static bool isLeftParenthesis(char c);
    static bool isRightParenthesis(char c);
    static std::string infixToPostfix(const std::string& infixExpression);
    static void handleOperand(Shunt& shunt, char c);
    static void handleOperator(Shunt& shunt, char c);
    static void handleLeftParenthesis(Shunt& shunt, char c);
    static void handleRightParenthesis(Shunt& shunt);
    static void cleanUpStack(Shunt& shunt);
    static void handleNextCharacter(Shunt& shunt, char c);
};
// ai-gen end
