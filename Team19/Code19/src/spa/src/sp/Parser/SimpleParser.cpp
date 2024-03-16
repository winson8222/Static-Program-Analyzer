#include "SimpleParser.h"
#include <stdexcept>
#include <iostream>
#include <unordered_map>
#include <functional>

/**
 * @brief Constructs a new Simple Parser object
 *
 * Reads the given file, tokenizes it and prepares for parsing.
 *
 * @param filename The name of the file to parse.
 */
SimpleParser::SimpleParser(std::shared_ptr<std::vector<LexicalToken>> tokens) {
	this->tokenStream = std::make_unique<SimpleTokenStream>(std::move(tokens));
	this->lineManager = std::make_unique<SimpleLineManager>();
}

/**
 * @brief Parses the entire program and returns a tree representing it.
 *
 * @return std::shared_ptr<ASTNode> A pointer to the root of the parse tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseProgram() {
	std::vector<std::shared_ptr<ASTNode>> procedures;

	while (this->tokenStream->hasTokensLeft()) {
		procedures.push_back(this->parseProcedure());
	}

	std::shared_ptr<ASTNode> root = this->createNode(ASTNodeType::PROGRAMS, SimpleLineManager::getProgramLineNumber());

	for (auto& procedure : procedures) {
		root->addChild(procedure);
	}

	SimpleCallLinker simpleCallLinker(root);
	simpleCallLinker.linkAllCallsToProcedure();

	return root;
}

std::shared_ptr<ASTNode> SimpleParser::createNode(ASTNodeType type, int lineNumber, std::string nodeValue) {
	if (nodeValue.empty()) {
		nodeValue = ASTUtility::getASTNodeType.find(type)->second;
	}

	return std::make_shared<ASTNode>(type, lineNumber, nodeValue);
}

std::shared_ptr<ASTNode> SimpleParser::parseProcedure() {
	if (!this->tokenStream->hasTokensLeft()) {
		throw std::runtime_error("Error: SimpleParser::parseProcedure encounter empty statement.");
	}

	this->tokenStream->popAndAssertToken(LexicalTokenType::KEYWORD_PROCEDURE);

	std::shared_ptr<ASTNode> procedureName = this->parseProcName();

	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> statementList = this->parseStmtLst();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_CLOSE_BRACE);

	std::shared_ptr<ASTNode> procedureTree = this->createNode(ASTNodeType::PROCEDURE, this->lineManager->getLine(), procedureName->getValue());

	procedureTree->addChild(statementList);
	return procedureTree;

}

std::shared_ptr<ASTNode> SimpleParser::parseStmtLst() {
	std::vector<std::shared_ptr<ASTNode>> statements;

	std::shared_ptr<ASTNode> statementListTree = this->createNode(ASTNodeType::STATEMENT_LIST, this->lineManager->getLine());

	// Parse every statement until we see a closing bracket.
	while (!this->tokenStream->peekToken().isType(LexicalTokenType::SYMBOL_CLOSE_BRACE)) {
		this->lineManager->nextLine();
		statements.push_back(this->parseStmt());
	}

	for (auto& statement : statements) {
		statementListTree->addChild(statement);
	}

	return statementListTree;
}

// ai-gen start(gpt, 2, e)
// Prompt: https://platform.openai.com/playground/p/f2k5TIcmcUShJEcyjSweZOMD?mode=chat
std::shared_ptr<ASTNode> SimpleParser::parseStmt() {
	// If next next token is '=', we are assigning. Call assign.
	LexicalToken secondToken = this->tokenStream->peekToken(2);
	if (secondToken.isType(LexicalTokenType::OPERATOR_ASSIGN)) {
		return this->parseAssign();
	}

	LexicalToken firstToken = this->tokenStream->peekToken();

	// Define the function map
	std::unordered_map<LexicalTokenType, std::function<std::shared_ptr<ASTNode>()>> parseFunctions = {
		{ LexicalTokenType::KEYWORD_CALL, [&]() { return this->parseCall(); } },
		{ LexicalTokenType::KEYWORD_PRINT, [&]() { return this->parsePrint(); } },
		{ LexicalTokenType::KEYWORD_READ, [&]() { return this->parseRead(); } },
		{ LexicalTokenType::KEYWORD_IF, [&]() { return this->parseIf(); } },
		{ LexicalTokenType::KEYWORD_WHILE, [&]() { return this->parseWhile(); } }
	};

	// Find the appropriate function and execute it
	auto parseFunctionIt = parseFunctions.find(firstToken.getTokenType());
	if (parseFunctionIt != parseFunctions.end()) {
		return parseFunctionIt->second();
	}

	// If no keyword is found, this is an invalid statement
	throw std::runtime_error("Error: Tried to parse statement, but input statement is not Assign, Call, Print, Read, If, or While statement.");
}
// ai-gen end

std::shared_ptr<ASTNode> SimpleParser::parseRead() {
	this->tokenStream->popAndAssertToken(LexicalTokenType::KEYWORD_READ);
	std::shared_ptr<ASTNode> variable = this->parseVarName();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_SEMICOLON);

	std::shared_ptr<ASTNode> readTree = this->createNode(ASTNodeType::READ, this->lineManager->getLine());

	readTree->addChild(variable);

	return readTree;
}

std::shared_ptr<ASTNode> SimpleParser::parsePrint() {
	this->tokenStream->popAndAssertToken(LexicalTokenType::KEYWORD_PRINT);
	std::shared_ptr<ASTNode> variable = this->parseVarName();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_SEMICOLON);

	std::shared_ptr<ASTNode> printTree = this->createNode(ASTNodeType::PRINT, this->lineManager->getLine());

	printTree->addChild(variable);

	return printTree;
}

std::shared_ptr<ASTNode> SimpleParser::parseCall() {
	this->tokenStream->popAndAssertToken(LexicalTokenType::KEYWORD_CALL);
	std::shared_ptr<ASTNode> variable = this->parseVarName();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_SEMICOLON);

	std::shared_ptr<ASTNode> callTree = this->createNode(ASTNodeType::CALL, this->lineManager->getLine());

	callTree->addChild(variable);

	return callTree;
}

std::shared_ptr<ASTNode> SimpleParser::parseWhile() {
	this->tokenStream->popAndAssertToken(LexicalTokenType::KEYWORD_WHILE);
	std::shared_ptr<ASTNode> whileTree = this->createNode(ASTNodeType::WHILE, this->lineManager->getLine());

	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> condExpr = this->parseCondExpr();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_CLOSE_PAREN);

	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> stmtLst = this->parseStmtLst();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_CLOSE_BRACE);

	whileTree->addChild(condExpr);
	whileTree->addChild(stmtLst);

	return whileTree;
}

std::shared_ptr<ASTNode> SimpleParser::parseIf() {
	this->tokenStream->popAndAssertToken(LexicalTokenType::KEYWORD_IF);
	std::shared_ptr<ASTNode> ifTree = this->createNode(ASTNodeType::IF_ELSE_THEN, this->lineManager->getLine());

	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> condExpr = this->parseCondExpr();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_CLOSE_PAREN);

	this->tokenStream->popAndAssertToken(LexicalTokenType::KEYWORD_THEN);
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> thenStmtLst = this->parseStmtLst();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_CLOSE_BRACE);

	this->tokenStream->popAndAssertToken(LexicalTokenType::KEYWORD_ELSE);
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> elseStmtLst = this->parseStmtLst();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_CLOSE_BRACE);

	ifTree->addChild(condExpr);
	ifTree->addChild(thenStmtLst);
	ifTree->addChild(elseStmtLst);

	return ifTree;
}

std::shared_ptr<ASTNode> SimpleParser::parseAssign() {
	std::shared_ptr<ASTNode> variable = this->parseVarName();

	this->tokenStream->popAndAssertToken(LexicalTokenType::OPERATOR_ASSIGN);
	std::shared_ptr<ASTNode> assignNode = this->createNode(ASTNodeType::ASSIGN, this->lineManager->getLine());

	std::shared_ptr<ASTNode> expr = this->parseExpr();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_SEMICOLON);

	assignNode->addChild(variable);
	assignNode->addChild(expr);

	return assignNode;
}

std::shared_ptr<ASTNode> SimpleParser::parseCondExpr() {
	LexicalToken firstToken = this->tokenStream->peekToken();

	if (firstToken.isType(LexicalTokenType::NAME) || firstToken.isType(LexicalTokenType::INTEGER)) {
		return this->parseRelExpr();
	}

	std::shared_ptr<ASTNode> operationNode;
	// If of form '!' '(' cond_expr ')'.
	if (firstToken.isType(LexicalTokenType::OPERATOR_NOT)) {
		this->tokenStream->popAndAssertToken(LexicalTokenType::OPERATOR_NOT);
		this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_OPEN_PAREN);

		std::shared_ptr<ASTNode> condExpr = this->parseCondExpr(); // Recursive parsing of cond_expr

		this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_CLOSE_PAREN);

		operationNode = this->createNode(ASTNodeType::NOT, this->lineManager->getLine());

		operationNode->addChild(condExpr);

		return operationNode;
	}

	// If of form  '(' cond_expr ')' '&&' '(' cond_expr ')' OR '(' cond_expr ')' '||' '(' cond_expr ')'
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> left = this->parseCondExpr();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_CLOSE_PAREN);

	// Retrieve logical operator (AND, OR)
	LexicalToken logicalOperator = this->tokenStream->peekToken();
	this->tokenStream->popAndAssertToken(LexicalTokenType::OPERATOR_CONDITIONAL);

	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> right = this->parseCondExpr();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_CLOSE_PAREN);

	ASTNodeType astType = LexicalTokenTypeMapper::lexicalToAstMap.at(logicalOperator.getTokenType());
	operationNode = this->createNode(astType, this->lineManager->getLine());

	operationNode->addChild(left);
	operationNode->addChild(right);

	return operationNode;
}

std::shared_ptr<ASTNode> SimpleParser::parseRelExpr() {
	std::shared_ptr<ASTNode> left = this->parseRelFactor();

	LexicalToken operatorToken = this->tokenStream->peekToken();
	this->tokenStream->popAndAssertToken(LexicalTokenType::OPERATOR_RELATIONAL);

	std::shared_ptr<ASTNode> right = this->parseRelFactor();

	ASTNodeType astType = LexicalTokenTypeMapper::lexicalToAstMap.at(operatorToken.getTokenType());
	std::shared_ptr<ASTNode> operationNode = this->createNode(astType, this->lineManager->getLine());

	operationNode->addChild(left);
	operationNode->addChild(right);

	return operationNode;
}

std::shared_ptr<ASTNode> SimpleParser::parseRelFactor() {
	return parseExpr();
}

// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/NGm3fHHy62WWafdKCc95vHpD?mode=chat
std::shared_ptr<ASTNode> SimpleParser::parseExpr() {
	std::shared_ptr<ASTNode> left = parseTerm();

	LexicalToken operation = this->tokenStream->peekToken();

	while (operation.isType(LexicalTokenType::OPERATOR_EXPR)) {
		// Consume operation token
		this->tokenStream->popAndAssertToken(LexicalTokenType::OPERATOR_EXPR);

		ASTNodeType astType = LexicalTokenTypeMapper::lexicalToAstMap.at(operation.getTokenType());
		std::shared_ptr<ASTNode> operationNode = this->createNode(astType, this->lineManager->getLine());

		std::shared_ptr<ASTNode> right = parseTerm();

		// Create a new AST node to combine the expr and term and add it under current operation
		operationNode->addChild(left);
		operationNode->addChild(right);

		// Swap left operand and operation for next iteration
		left = operationNode;
		operation = this->tokenStream->peekToken();
	}

	return left;
}

std::shared_ptr<ASTNode> SimpleParser::parseTerm() {
	std::shared_ptr<ASTNode> left = parseFactor();

	LexicalToken operation = this->tokenStream->peekToken();

	while (operation.isType(LexicalTokenType::OPERATOR_TERM)) {
		// Consume operation token
		this->tokenStream->popAndAssertToken(LexicalTokenType::OPERATOR_TERM);

		ASTNodeType astType = LexicalTokenTypeMapper::lexicalToAstMap.at(operation.getTokenType());
		std::shared_ptr<ASTNode> operationNode = this->createNode(astType, this->lineManager->getLine());

		std::shared_ptr<ASTNode> right = parseFactor();

		// Create a new AST node to combine the factor and term and add it under current operation
		operationNode->addChild(left);
		operationNode->addChild(right);

		// Swap left operand and operation for next iteration
		left = operationNode;
		operation = this->tokenStream->peekToken();
	}

	return left;
}
// ai-gen end

std::shared_ptr<ASTNode> SimpleParser::parseFactor() {
	LexicalToken nextToken = this->tokenStream->peekToken();

	if (nextToken.isType(LexicalTokenType::NAME)) {
		return this->parseVarName();
	}

	if (nextToken.isType(LexicalTokenType::INTEGER)) {
		return this->parseConstValue();
	}

	// Last case: (expr)
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> expr = parseExpr();
	this->tokenStream->popAndAssertToken(LexicalTokenType::SYMBOL_CLOSE_PAREN);
	return expr;
}

std::shared_ptr<ASTNode> SimpleParser::parseVarName() {
	LexicalToken variable = this->tokenStream->peekToken();
	this->tokenStream->popAndAssertToken(LexicalTokenType::NAME);
	return this->createNode(ASTNodeType::VARIABLE, this->lineManager->getLine(), variable.getValue());
}

std::shared_ptr<ASTNode> SimpleParser::parseProcName() {
	LexicalToken procedureName = this->tokenStream->peekToken();
	this->tokenStream->popAndAssertToken(LexicalTokenType::NAME);
	return this->createNode(ASTNodeType::VARIABLE, this->lineManager->getLine(), procedureName.getValue());
}

std::shared_ptr<ASTNode> SimpleParser::parseConstValue() {
	LexicalToken constant = this->tokenStream->peekToken();
	this->tokenStream->popAndAssertToken(LexicalTokenType::INTEGER);
	return this->createNode(ASTNodeType::CONSTANT, this->lineManager->getLine(), constant.getValue());
}
