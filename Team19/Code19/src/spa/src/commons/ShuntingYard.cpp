#include "ShuntingYard.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
std::string ShuntingYard::convertToPostfix(const std::string& infixExpression) {
  return infixToPostfix(infixExpression);
}

Precedence ShuntingYard::getPrecedence(char c) {
  if (c == '+' || c == '-') {
    return Precedence::LOW;
  } else if (c == '*' || c == '/' || c == '%') {
    return Precedence::HIGH;
  } else {
    return Precedence::INVALID;
  }
}

std::string ShuntingYard::makeQuoted(char s) {
    std::string result = "'";
    result += s;
    result += "'";
    return result;
}

bool ShuntingYard::isOperator(char c) {
  return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
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

void ShuntingYard::handleOperand(Shunt& shunt, char c) {
  if (!shunt.getPrevOperand()) {
      shunt.addStringToPostfixExpression("'");
  }
  shunt.setPrevOperand(true);
  shunt.addCharToPostfixExpression(c);
}

void ShuntingYard::handleOperator(Shunt& shunt, char c) {
  if (shunt.getPrevOperand()) {
    shunt.addStringToPostfixExpression("'");
    shunt.setPrevOperand(false);
  }
  while (!shunt.getStack().empty() && isOperator(shunt.getStack().top()) && (getPrecedence(c) <= getPrecedence(shunt.getStack().top()))) {
      shunt.addStringToPostfixExpression(makeQuoted(shunt.popFromStack()));
  }
  shunt.addToStack(c);
}

void ShuntingYard::handleLeftParenthesis(Shunt& shunt, char c) {
    if (shunt.getPrevOperand()) {
        shunt.addStringToPostfixExpression("'");
        shunt.setPrevOperand(false);
    }
    shunt.addToStack(c);
}

void ShuntingYard::handleRightParenthesis(Shunt& shunt) {
    if (shunt.getPrevOperand()) {
        shunt.addStringToPostfixExpression("'");
        shunt.setPrevOperand(false);
    }
    while (!shunt.getStack().empty() && !isLeftParenthesis(shunt.getStack().top())) {
        shunt.addStringToPostfixExpression(makeQuoted(shunt.popFromStack()));
    }
    shunt.popFromStack();
}

void ShuntingYard::cleanUpStack(Shunt& shunt) {
    while (!shunt.getStack().empty()) {
        if (shunt.getPrevOperand()) {
            shunt.addStringToPostfixExpression("'");
            shunt.setPrevOperand(false);
        }
        shunt.addStringToPostfixExpression(makeQuoted(shunt.popFromStack()));
    }
}

void ShuntingYard::handleNextCharacter(Shunt& shunt, char c) {
    if (isOperand(c)) {
        handleOperand(shunt, c);
    } else if (isOperator(c)) {
        handleOperator(shunt, c);
    } else if (isLeftParenthesis(c)) {
        handleLeftParenthesis(shunt, c);
    } else if (isRightParenthesis(c)) {
        handleRightParenthesis(shunt);
    }
}

std::string ShuntingYard::infixToPostfix(const std::string& infixExpression) {
    Shunt shunt = Shunt();
    for (char c : infixExpression) {
        if (c == ' ') continue;
        handleNextCharacter(shunt, c);
    }
    cleanUpStack(shunt);
    return shunt.getPostfixExpression();
}
// ai-gen end
