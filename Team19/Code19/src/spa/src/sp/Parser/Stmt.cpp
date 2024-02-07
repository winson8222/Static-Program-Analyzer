#include "Stmt.h"
#include <iostream>

Stmt::Stmt(const std::string& stmtType)
    : stmtType(stmtType) {}

void Stmt::buildTree() const {
    // Do sth
}