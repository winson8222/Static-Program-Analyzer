#pragma once

#include "ASTNode.h"

#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>


struct EnumClassHash {
    template <typename T> std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};

/*
How to use:
1. AST with default root node
2. 
*/

class AST {
public:
public:
    AST(std::unique_ptr<ASTNode> root);
    const ASTNode* getRoot() const;

private:
    std::unique_ptr<ASTNode> root;
};

class Utility {
public:
    static std::string getTNodeTypeString(ASTNodeType t);
    static std::string getOperatorStringFromTNodeType(ASTNodeType t);
    static std::string getExprString(const ASTNode& tNode);
};