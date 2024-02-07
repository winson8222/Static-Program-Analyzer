#include "Procedure.h"
#include <iostream>

Procedure::Procedure() {

}

void Procedure::addStmtList(StmtList stmtList) {
    this->statementLists.push_back(stmtList);
}

void Procedure::buildTree() const {
    // Do sth
}

int Procedure::getStartLine() const {
    return 0;
    // Do sth
}

int Procedure::getEndLine() const {
    return 0;
    // Do sth
}
