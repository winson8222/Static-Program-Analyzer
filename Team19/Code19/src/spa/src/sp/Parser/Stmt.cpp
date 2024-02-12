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
    // IMPORTANT: In the future, want to make Stmt Abstract class/Interface, and inherit everything in Stmt.

    // **IMPORTANT** Placeholder implementation to avoid compilation error.
    std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
        ASTNodeType::ERROR, 0, "Stmt::buildTree() not implemented."
    );

    return tree;
}