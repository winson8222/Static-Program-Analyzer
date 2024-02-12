#include "Procedure.h"
#include <iostream>

Procedure::Procedure() {

}

void Procedure::addStmtList(StmtList stmtList) {
    this->statementLists.push_back(stmtList);
}

std::shared_ptr<ASTNode> Procedure::buildTree() {
    std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
        ASTNodeType::ERROR, 0, ""
    );

    return tree;
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
