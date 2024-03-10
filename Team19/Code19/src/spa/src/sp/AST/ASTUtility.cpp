#include "sp/AST/ASTUtility.h"
#include <sstream>

// ai-gen start (gpt, 2, e)
// prompt: https://chat.openai.com/share/a181de60-e76f-496c-9bee-7ea80f2be651 and GitHub Copilot

std::unordered_map<ASTNodeType, std::string> ASTUtility::getASTNodeType{
	{ASTNodeType::PROGRAMS, "Program"},
	{ASTNodeType::PROCEDURE, "procedure"},
	{ASTNodeType::STATEMENT_LIST, "stmtLst"},
	{ASTNodeType::ASSIGN, "assign"},
	{ASTNodeType::CALL, "call"},
	{ASTNodeType::IF_ELSE_THEN, "if"},
	{ASTNodeType::PRINT, "print"},
	{ASTNodeType::READ, "read"},
	{ASTNodeType::WHILE, "while"},
	{ASTNodeType::NOT, "!"},
	{ASTNodeType::AND, "&&"},
	{ASTNodeType::OR, "||"},
	{ASTNodeType::GREATER, ">"},
	{ASTNodeType::GREATER_OR_EQUAL, ">="},
	{ASTNodeType::LESSER, "<"},
	{ASTNodeType::LESSER_OR_EQUAL, "<="},
	{ASTNodeType::EQUAL, "=="},
	{ASTNodeType::NOT_EQUAL, "!="},
	{ASTNodeType::ADD, "+"},
	{ASTNodeType::SUBTRACT, "-"},
	{ASTNodeType::MULTIPLY, "*"},
	{ASTNodeType::DIVIDE, "/"},
	{ASTNodeType::MODULO, "%"},
	{ASTNodeType::VARIABLE, "Variable"},
	{ASTNodeType::CONSTANT, "Constant"},
	{ASTNodeType::ERROR, "Error"}
};


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