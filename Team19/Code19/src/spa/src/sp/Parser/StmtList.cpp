#include "StmtList.h"
#include <iostream>

StmtList::StmtList() {}

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
    // **IMPORTANT** Placeholder implementation to avoid compilation error.
    std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
        ASTNodeType::ERROR, 0, "StmtList::buildTree not implemented."
    );

	return tree;
}