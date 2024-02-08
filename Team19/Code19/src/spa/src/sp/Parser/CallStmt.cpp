#include "CallStmt.h"
#include <iostream>

CallStmt::CallStmt(LexicalToken variable, int start, int end) {
    this->variable = variable;
    this->lines = std::pair<int>(start, end);
}

int CallStmt::getStartLine() const {
    return 0;
    // Do sth
}

int CallStmt::getEndLine() const {
    return 0;
    // Do sth
}

void CallStmt::buildTree() const {
    // Do sth
}