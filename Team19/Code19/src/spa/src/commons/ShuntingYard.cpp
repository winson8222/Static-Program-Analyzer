#include "ShuntingYard.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
std::string ShuntingYard::convertToPostfix(const std::string& infixExpression) {
  return infixToPostfix(infixExpression);
}

Precedence ShuntingYard::getPrecedence(char c) {
  if (c == PLUS || c == MINUS) {
    return Precedence::LOW;
  } else if (c == MULTIPLY || c == DIVIDE || c == MODULO) {
    return Precedence::HIGH;
  } else {
    return Precedence::INVALID;
  }
}

std::string ShuntingYard::makeQuoted(char s) {
    std::string result;
    result += QUOTE;
    result += s;
    result += QUOTE;
    return result;
}

bool ShuntingYard::isOperator(char c) {
  return c == PLUS || c == MINUS || c == MULTIPLY || c == DIVIDE || c == MODULO;
}

bool ShuntingYard::isOperand(char c) {
  return c >= ZERO && c <= NINE || c >= LOWER_A && c <= LOWER_Z || c >= UPPER_A && c <= UPPER_Z;
}

bool ShuntingYard::isLeftParenthesis(char c) {
  return c == LEFT_PARENTHESIS;
}

bool ShuntingYard::isRightParenthesis(char c) {
  return c == RIGHT_PARENTHESIS;
}

void ShuntingYard::handleOperand(Shunt& shunt, char c) {
    if (!shunt.getPrevOperand()) {
      shunt.addStringToPostfixExpression(std::string(1, QUOTE));
    }
    shunt.setPrevOperand(true);
    shunt.addCharToPostfixExpression(c);
}

void ShuntingYard::handleOperator(Shunt& shunt, char c) {
    handleEndOfExpression(shunt);
    while (!shunt.getStack().empty() && isOperator(shunt.getStack().top()) && (getPrecedence(c) <= getPrecedence(shunt.getStack().top()))) {
      shunt.addStringToPostfixExpression(makeQuoted(shunt.popFromStack()));
    }
    shunt.addToStack(c);
}

void ShuntingYard::handleLeftParenthesis(Shunt& shunt, char c) {
    handleEndOfExpression(shunt);
    shunt.addToStack(c);
}

void ShuntingYard::handleRightParenthesis(Shunt& shunt) {
    handleEndOfExpression(shunt);
    while (!shunt.getStack().empty() && !isLeftParenthesis(shunt.getStack().top())) {
        shunt.addStringToPostfixExpression(makeQuoted(shunt.popFromStack()));
    }
    shunt.popFromStack();
}

void ShuntingYard::cleanUpStack(Shunt& shunt) {
    while (!shunt.getStack().empty()) {
        handleEndOfExpression(shunt);
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
        if (c == SPACE) continue;
        handleNextCharacter(shunt, c);
    }
    cleanUpStack(shunt);
    if (shunt.getPrevOperand()) shunt.addStringToPostfixExpression(std::string(1, QUOTE));
    return shunt.getPostfixExpression();
}

void ShuntingYard::handleEndOfExpression(Shunt& shunt) {
    if (shunt.getPrevOperand()) {
        shunt.addStringToPostfixExpression(std::string(1, QUOTE));
        shunt.setPrevOperand(false);
    }
}
// ai-gen end
