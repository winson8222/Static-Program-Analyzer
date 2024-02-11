#pragma once

#include "ASTNode.h"

#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>


class AST {
public:
    AST(std::unique_ptr<ASTNode> root);
    const ASTNode* getRoot() const;

private:
    std::unique_ptr<ASTNode> root;
};