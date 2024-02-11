#include "ASTNode.h"
#include "Utility.h"
#include <sstream>

std::string Utility::getASTNodeType(ASTNodeType t) {
    switch (t) {
        case ASTNodeType::PROGRAMS:
            return "Program";
        case ASTNodeType::PROCEDURE:
            return "procedure";
        case ASTNodeType::STATEMENT_LIST:
            return "stmtLst";
        case ASTNodeType::ASSIGN:
            return "assign";
        case ASTNodeType::CALL:
            return "call";
        case ASTNodeType::IF_ELSE_THEN:
            return "if-else-then";
        case ASTNodeType::PRINT:
            return "print";
        case ASTNodeType::READ:
            return "read";
        case ASTNodeType::WHILE:
            return "while";
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
        case ASTNodeType::VARIABLE:
            return "Variable";
        case ASTNodeType::CONSTANT:
            return "Constant";
        case ASTNodeType::ERROR:
            return "error";
        default:
            throw "Error";
    };
}
