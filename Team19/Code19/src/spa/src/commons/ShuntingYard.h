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
    static void handleEndOfExpression(Shunt& shunt);
    static const char MINUS = '-';
    static const char PLUS = '+';
    static const char MULTIPLY = '*';
    static const char DIVIDE = '/';
    static const char MODULO = '%';
    static const char LEFT_PARENTHESIS = '(';
    static const char RIGHT_PARENTHESIS = ')';
    static const char QUOTE = '\'';
    static const char ZERO = '0';
    static const char NINE = '9';
    static const char LOWER_A = 'a';
    static const char LOWER_Z = 'z';
    static const char UPPER_A = 'A';
    static const char UPPER_Z = 'Z';
    static const char SPACE = ' ';
};
// ai-gen end
