#include "sp/Utility.h"
#include <sstream>

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651

std::string Utility::getASTNodeType(ASTNodeType t) {
    switch (t) {
        case ASTNodeType::PROGRAMS:
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
            return "IfElseThen";
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
            return "GreaterOrEqual";
        case ASTNodeType::LESSER:
            return "Lesser";
        case ASTNodeType::LESSER_OR_EQUAL:
            return "LesserOrEqual";
        case ASTNodeType::EQUAL:
            return "EqualEqual";
        case ASTNodeType::NOT_EQUAL:
            return "NotEqual";
        case ASTNodeType::ADD:
            return "Add";
        case ASTNodeType::SUBTRACT:
            return "Subtract";
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
            return "Error";
        default:
            throw "Error";
    };
}

std::string Utility::getDesignType(ASTNodeType t) {
    return getASTNodeType(t);
}

bool Utility::nodeIsStatement(ASTNodeType t) {
    return t == ASTNodeType::ASSIGN || t == ASTNodeType::CALL 
        || t == ASTNodeType::IF_ELSE_THEN || t == ASTNodeType::PRINT 
        || t == ASTNodeType::READ || t == ASTNodeType::WHILE;
}

// ai-gen end