#include "StmtList.h"
#include <iostream>

StmtList::StmtList() {

}

void StmtList::addStmt(std::shared_ptr<Stmt> stmt) {
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

std::shared_ptr<ASTNode> StmtList::buildTree() {
    // Do sth
    std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
        ASTNodeType::CALL, this->lines.first, Utility::getASTNodeType(ASTNodeType::CALL)
    );

    return tree;

}