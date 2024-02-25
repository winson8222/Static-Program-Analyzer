#include "sp/AST/ASTUtility.h"
#include <sstream>

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651 and GitHub Copilot

std::string ASTUtility::getASTNodeType(ASTNodeType t) {
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
            return "Error";
        default:
            throw "Error";
    };
}

bool ASTUtility::nodeIsStatement(ASTNodeType t) {
    return t == ASTNodeType::ASSIGN || t == ASTNodeType::CALL 
        || t == ASTNodeType::IF_ELSE_THEN || t == ASTNodeType::PRINT 
        || t == ASTNodeType::READ || t == ASTNodeType::WHILE;
}

bool ASTUtility::nodeIsRelExpression(ASTNodeType t) {
	return  t == ASTNodeType::GREATER || t == ASTNodeType::GREATER_OR_EQUAL 
        || t == ASTNodeType::LESSER || t == ASTNodeType::LESSER_OR_EQUAL 
        || t == ASTNodeType::EQUAL || t == ASTNodeType::NOT_EQUAL;
}

bool ASTUtility::nodeIsCondExpression(ASTNodeType t) {
	return t == ASTNodeType::AND || t == ASTNodeType::OR 
		|| t == ASTNodeType::NOT;
}
bool ASTUtility::nodeIsValidOperator(ASTNodeType t) {
	return t == ASTNodeType::ADD || t == ASTNodeType::SUBTRACT 
		|| t == ASTNodeType::MULTIPLY || t == ASTNodeType::DIVIDE 
		|| t == ASTNodeType::MODULO;
}

bool ASTUtility::nodeIsValidRelFactor(ASTNodeType t) {
	return t == ASTNodeType::VARIABLE || t == ASTNodeType::CONSTANT;
}

bool ASTUtility::nodeCanFormValidExpression(ASTNodeType t) {
    return nodeIsRelExpression(t)
        || nodeIsCondExpression(t)
        || nodeIsValidOperator(t)
        || nodeIsValidRelFactor(t);
}

bool ASTUtility::nodeIsProgram(ASTNodeType t) {
	return t == ASTNodeType::PROGRAMS;
}

bool ASTUtility::nodeIsProcedure(ASTNodeType t) {
	return t == ASTNodeType::PROCEDURE;
}

bool ASTUtility::nodeIsStatementList(ASTNodeType t) {
	return t == ASTNodeType::STATEMENT_LIST;
}

bool ASTUtility::nodeIsIfElse(ASTNodeType t) {
	return t == ASTNodeType::IF_ELSE_THEN;
}
// ai-gen end