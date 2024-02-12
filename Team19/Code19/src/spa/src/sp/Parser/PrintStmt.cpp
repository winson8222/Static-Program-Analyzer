#include "PrintStmt.h"
#include <iostream>

PrintStmt::PrintStmt(const LexicalToken& variable, int start, int end) {
    this->variable = variable;
    this->lines = std::make_pair(start, end); 
}

int PrintStmt::getStartLine() const {
    return this->lines.first;
}

int PrintStmt::getEndLine() const {
    return this->lines.second;
}

std::shared_ptr<ASTNode> PrintStmt::buildTree() {
    std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
        ASTNodeType::PRINT, this->lines.first, Utility::getASTNodeType(ASTNodeType::PRINT)
    );

    std::shared_ptr<ASTNode> child = std::make_shared<ASTNode>(
        ASTNodeType::VARIABLE, this->lines.second, this->variable.getValue()
    );

    tree.get()->addChild(child);

    return tree;
}