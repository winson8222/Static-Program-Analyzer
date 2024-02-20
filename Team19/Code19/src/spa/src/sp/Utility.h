#pragma once

#include "sp/AST/ASTNode.h"
#include <string>
#include <utility>
#include <vector>

class Utility {
public:
    static std::string getASTNodeType(ASTNodeType t);
    static std::string getDesignType(ASTNodeType t);
    static bool nodeIsStatement(ASTNodeType t);
    static bool nodeIsExpression(ASTNodeType t);
    static bool nodeIsConditionalOperator(ASTNodeType t);

    static bool nodeIsValidOperator(ASTNodeType t);
};