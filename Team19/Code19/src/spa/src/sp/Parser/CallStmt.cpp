#include "CallStmt.h"
#include "sp/LexicalToken.h"
#include <iostream>

CallStmt::CallStmt(const LexicalToken& variable, int start, int end) {
    this->variable = variable;
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