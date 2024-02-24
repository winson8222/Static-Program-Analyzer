#pragma once

#include "ASTNode.h"

#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

/*
* Plan for later implementation:
* This is a wrapper for an AST node. It is used to store the root of the AST,
* and to provide a way to access the root.
*/
class AST {
public:
    AST(std::shared_ptr<ASTNode> root);
    const ASTNode* getRoot() const;

private:
    std::shared_ptr<ASTNode> root;
};