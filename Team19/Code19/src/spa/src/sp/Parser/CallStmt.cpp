#include "CallStmt.h"
#include <iostream>

CallStmt::CallStmt(LexicalToken variable, int start, int end) {
    this->variable = variable;
    this->lines = std::pair<int>(start, end);
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