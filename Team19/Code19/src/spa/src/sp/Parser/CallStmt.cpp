#include "CallStmt.h"
#include <iostream>

CallStmt::CallStmt(LexicalToken variable, int start, int end) {
    this->variable = LexicalToken(variable.getTokenType(), variable.getLine(), variable.getLinePosition(), variable.getValue());
    this->lines = std::make_pair(start, end); 
}

int CallStmt::getStartLine() const {
    return this->lines.first;
}

int CallStmt::getEndLine() const {
    return this->lines.second;
}

void CallStmt::buildTree() const {
    // Do sth
}