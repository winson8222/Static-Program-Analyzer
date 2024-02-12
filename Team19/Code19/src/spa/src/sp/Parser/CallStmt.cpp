#include "CallStmt.h"
#include "sp/LexicalToken.h"
#include <iostream>

CallStmt::CallStmt(const LexicalToken& variable, int start, int end) {
    this->variable = variable;
    this->lines = std::make_pair(start, end); 
}

int CallStmt::getStartLine() const {
    return this->lines.first;
}

int CallStmt::getEndLine() const {
    return this->lines.second;
}

std::shared_ptr<ASTNode> CallStmt::buildTree() {
    std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
        ASTNodeType::CALL, this->lines.first, Utility::getASTNodeType(ASTNodeType::CALL)
    );

    std::shared_ptr<ASTNode> child = std::make_shared<ASTNode>(
        ASTNodeType::VARIABLE, this->lines.second, this->variable.getValue()
    );

    tree.get()->addChild(child);

    return tree;
}