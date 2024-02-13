#pragma once

#include "ASTNode.h"

#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>


class AST {
public:
    AST(std::shared_ptr<ASTNode> root);
    const ASTNode* getRoot() const;

private:
    std::shared_ptr<ASTNode> root;
};