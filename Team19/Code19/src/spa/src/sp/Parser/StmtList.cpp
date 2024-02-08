#include "StmtList.h"
#include <iostream>

StmtList::StmtList() {

}

void StmtList::addStmt(Stmt stmt) {
    this->statements.push_back(stmt);
}

int StmtList::getStartLine() const {
    return 0;
    // Do sth
}

int StmtList::getEndLine() const {
    return 0;
    // Do sth
}

void StmtList::buildTree() const {
    // Do sth
}