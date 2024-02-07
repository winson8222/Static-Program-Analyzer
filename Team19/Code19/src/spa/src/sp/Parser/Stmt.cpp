#include "Stmt.h"
#include <iostream>

Stmt::Stmt(const std::string& stmtType)
    : stmtType(stmtType) {}

int Stmt::getStartLine() const {
    // Do sth
}

int Stmt::getEndLine() const {
    // Do sth
}

void Stmt::buildTree() const {
    // Do sth
}