#include "Shunt.h"


// ai-gen start(copilot, 0, e)
// prompt: used copilot
Shunt::Shunt() {
    postfixExpression = "";
    prevOperand = false;
}

bool Shunt::getPrevOperand() const {
    return prevOperand;
}

std::string Shunt::getPostfixExpression() {
    return postfixExpression;
}

std::stack<char> Shunt::getStack() {
    return stack;
}

void Shunt::setPrevOperand(bool prevOperand) {
    this->prevOperand = prevOperand;
}

void Shunt::addStringToPostfixExpression(std::string s) {
    postfixExpression += s;
}

void Shunt::addCharToPostfixExpression(char c) {
    postfixExpression += c;
}

void Shunt::addToStack(char c) {
    stack.push(c);
}

char Shunt::popFromStack() {
    char c = stack.top();
    stack.pop();
    return c;
}

// ai-gen end