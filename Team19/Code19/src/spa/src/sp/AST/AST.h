#pragma once

#include "ASTNode.h"

class AST {
public:
    AST(std::unique_ptr<ASTNode> root);

    const ASTNode* getRoot() const;

private:
    std::unique_ptr<ASTNode> root;
};