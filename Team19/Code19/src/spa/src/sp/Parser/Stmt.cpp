#include "Stmt.h"
#include <iostream>

Stmt::Stmt() {}

int Stmt::getStartLine() const {
    return 0;
    // Do sth
}

int Stmt::getEndLine() const {
    return 0;
    // Do sth
}

std::shared_ptr<ASTNode> Stmt::buildTree() {
    // Do sth
    std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
        ASTNodeType::CALL, this->lines.first, Utility::getASTNodeType(ASTNodeType::CALL)
    );

    return tree;
}