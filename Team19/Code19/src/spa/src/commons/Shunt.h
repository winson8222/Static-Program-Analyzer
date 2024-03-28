#pragma once

#include <string>
#include <stack>

class Shunt {
private:
    std::string postfixExpression;
    std::stack<char> stack;
    bool prevOperand;
public:
    Shunt();
    bool getPrevOperand() const;
    std::string getPostfixExpression();
    std::stack<char> getStack();
    void setPrevOperand(bool prevOperand);
    void addStringToPostfixExpression(std::string c);
    void addCharToPostfixExpression(char c);
    void addToStack(char c);
    char popFromStack();
};
