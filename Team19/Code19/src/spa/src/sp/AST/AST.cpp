#include "AST.h"
#include "ASTNode.h"

AST::AST(std::unique_ptr<ASTNode> root) : root(std::move(root)) {}

const ASTNode* AST::getRoot() const {
    return root.get();
}


std::string Utility::getTNodeTypeString(ASTNodeType t) {
    switch (t) {
    case ASTNodeType::PROGRAM:
        return "Program";
    case ASTNodeType::PROCEDURE:
        return "Procedure";
    case ASTNodeType::STATEMENT_LIST:
        return "StatementList";
    case ASTNodeType::ASSIGN:
        return "Assign";
    case ASTNodeType::CALL:
        return "Call";
    case ASTNodeType::IF_ELSE_THEN:
        return "IfElse";
    case ASTNodeType::PRINT:
        return "Print";
    case ASTNodeType::READ:
        return "Read";
    case ASTNodeType::WHILE:
        return "While";
    case ASTNodeType::NOT:
        return "Not";
    case ASTNodeType::AND:
        return "And";
    case ASTNodeType::OR:
        return "Or";
    case ASTNodeType::GREATER:
        return "Greater";
    case ASTNodeType::GREATER_OR_EQUAL:
        return "Greater than or Equal";
    case ASTNodeType::LESSER:
        return "Lesser";
    case ASTNodeType::LESSER_OR_EQUAL:
        return "Lesser than or Equal";
    case ASTNodeType::EQUAL:
        return "Equal";
    case ASTNodeType::NOT_EQUAL:
        return "NotEqual";
    case ASTNodeType::ADD:
        return "Plus";
    case ASTNodeType::SUBTRACT:
        return "Minus";
    case ASTNodeType::MULTIPLY:
        return "Multiply";
    case ASTNodeType::DIVIDE:
        return "Divide";
    case ASTNodeType::MODULO:
        return "Modulo";
    case ASTNodeType::VARIABLE:
        return "Variable";
    case ASTNodeType::CONSTANT:
        return "Constant";
    case ASTNodeType::ERROR:
        return "INVALID";
    default:
        throw "Error: Unknown AST is not implemented yet.";
    };
}

std::string Utility::getOperatorStringFromTNodeType(ASTNodeType t) {
    switch (t) {
    case ASTNodeType::NOT:
        return "!";
    case ASTNodeType::AND:
        return "&&";
    case ASTNodeType::OR:
        return "||";
    case ASTNodeType::GREATER:
        return ">";
    case ASTNodeType::GREATER_OR_EQUAL:
        return ">=";
    case ASTNodeType::LESSER:
        return "<";
    case ASTNodeType::LESSER_OR_EQUAL:
        return "<=";
    case ASTNodeType::EQUAL:
        return "==";
    case ASTNodeType::NOT_EQUAL:
        return "!=";
    case ASTNodeType::ADD:
        return "+";
    case ASTNodeType::SUBTRACT:
        return "-";
    case ASTNodeType::MULTIPLY:
        return "*";
    case ASTNodeType::DIVIDE:
        return "/";
    case ASTNodeType::MODULO:
        return "%";
    default:
        throw "Error: getOperatorTNodeTypeString only takes in an operator type";
    };
}

std::string Utility::getExprString(const ASTNode& tNode) {
    return "";
}