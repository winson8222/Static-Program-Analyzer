#include "ReadStmt.h"
#include <iostream>

ReadStmt::ReadStmt(const LexicalToken& variable, int start, int end) {
    this->variable = variable;
    this->lines = std::make_pair(start, end); 
}

int ReadStmt::getStartLine() const {
    return this->lines.first;
}

int ReadStmt::getEndLine() const {
    return this->lines.second;
}

std::shared_ptr<ASTNode> ReadStmt::buildTree() {
    std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
        ASTNodeType::READ, this->lines.first, Utility::getASTNodeType(ASTNodeType::READ)
    );

    std::shared_ptr<ASTNode> child = std::make_shared<ASTNode>(
        ASTNodeType::VARIABLE, this->lines.second, this->variable.getValue()
    );

    tree.get()->addChild(child);

    return tree;
}