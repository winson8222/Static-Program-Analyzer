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
	this->tokenStream = std::make_unique<SimpleTokenStream>(tokens);
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

/**
 * @brief Assert Token to check if the token's type matches the expected one.
 *
 * @param token A lexical token in the stream.
 * @param type A expected lexical token type.
 * @throws Retrieves a runtime_error if the token's type doesn't match the expected type.
 */
void SimpleParser::assertToken(LexicalToken token, LexicalTokenType type) const {
	if (!token.isType(type)) {
		throw std::runtime_error("Error: Expected " + LexicalTokenTypeMapper::printType(type) + " but got " + LexicalTokenTypeMapper::printType(token.getTokenType()) +
			" At Program Line " + std::to_string(this->lineManager->getLine()));
	}
}

std::shared_ptr<ASTNode> SimpleParser::createNode(ASTNodeType type, int lineNumber, std::string nodeValue) {
	if (nodeValue.empty()) {
		nodeValue = ASTUtility::getASTNodeType.find(type)->second;
	}

	return std::make_shared<ASTNode>(type, lineNumber, nodeValue);
}

/**
 * @brief Parse a procedure in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed procedure node tree.
 * @throws Retrieves a runtime_error if parsing is unsuccessful.
 */
std::shared_ptr<ASTNode> SimpleParser::parseProcedure() {
	if (!this->tokenStream->hasTokensLeft()) {
		throw std::runtime_error("Error: SimpleParser::parseProcedure encounter empty statement.");
	}

	LexicalToken procedureKeyword = this->tokenStream->getNextToken();
	this->assertToken(procedureKeyword, LexicalTokenType::KEYWORD_PROCEDURE);

	std::shared_ptr<ASTNode> procedureName = this->parseProcName();

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> statementList = this->parseStmtLst();
	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_BRACE);

	std::shared_ptr<ASTNode> procedureTree = this->createNode(ASTNodeType::PROCEDURE, this->lineManager->getLine(), procedureName->value);

	procedureTree->addChild(statementList);
	return procedureTree;

}

/**
 * @brief Parse a list of statements in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed statement list node tree.
 */
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
/**
 * @brief Parse a statement in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed statement node tree.
 * @throws Retrieves a runtime_error if parsing is unsuccessful.
 */
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

/**
 * @brief Parse a read statement in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed read node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseRead() {
	LexicalToken keyword = this->tokenStream->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_READ);

	std::shared_ptr<ASTNode> variable = this->parseVarName();

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_SEMICOLON);

	std::shared_ptr<ASTNode> readTree = this->createNode(ASTNodeType::READ, this->lineManager->getLine());

	readTree->addChild(variable);

	return readTree;
}

/**
 * @brief Parse a print statement in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed print node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parsePrint() {
	LexicalToken keyword = this->tokenStream->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_PRINT);

	std::shared_ptr<ASTNode> variable = this->parseVarName();

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_SEMICOLON);

	std::shared_ptr<ASTNode> printTree = this->createNode(ASTNodeType::PRINT, this->lineManager->getLine());

	printTree->addChild(variable);

	return printTree;
}

/**
 * @brief Parse a call statement in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed call node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseCall() {
	LexicalToken keyword = this->tokenStream->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_CALL);

	std::shared_ptr<ASTNode> variable = this->parseVarName();

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_SEMICOLON);

	std::shared_ptr<ASTNode> callTree = this->createNode(ASTNodeType::CALL, this->lineManager->getLine());

	callTree->addChild(variable);

	return callTree;
}


/**
 * @brief Parse a while statement in the program.
 *
 * @details While statement can only take this form: 'while' '(' cond_expr ')' '{' stmtLst '}'
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed while node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseWhile() {
	LexicalToken keyword = this->tokenStream->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_WHILE);

	std::shared_ptr<ASTNode> whileTree = this->createNode(ASTNodeType::WHILE, this->lineManager->getLine());

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> condExpr = this->parseCondExpr();
	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> stmtLst = this->parseStmtLst();
	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_BRACE);


	whileTree->addChild(condExpr);
	whileTree->addChild(stmtLst);

	return whileTree;
}


/**
 * @brief Parse a if statement in the program.
 *
 * @details If statement can only take this form: 'if' '(' cond_expr ')' 'then' '{' stmtLst '}' 'else' '{' stmtLst '}'
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed if node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseIf() {
	LexicalToken keyword = this->tokenStream->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_IF);

	std::shared_ptr<ASTNode> ifTree = this->createNode(ASTNodeType::IF_ELSE_THEN, this->lineManager->getLine());

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> condExpr = this->parseCondExpr();
	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::KEYWORD_THEN);

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> thenStmtLst = this->parseStmtLst();
	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_BRACE);

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::KEYWORD_ELSE);

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> elseStmtLst = this->parseStmtLst();
	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_BRACE);

	ifTree->addChild(condExpr);
	ifTree->addChild(thenStmtLst);
	ifTree->addChild(elseStmtLst);

	return ifTree;
}

/**
 * @brief Parse a assign statement in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed assign node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseAssign() {
	std::shared_ptr<ASTNode> variable = this->parseVarName();

	LexicalToken assign = this->tokenStream->getNextToken();
	this->assertToken(assign, LexicalTokenType::OPERATOR_ASSIGN);
	std::shared_ptr<ASTNode> assignNode = this->createNode(ASTNodeType::ASSIGN, this->lineManager->getLine());

	std::shared_ptr<ASTNode> expr = this->parseExpr();
	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_SEMICOLON);

	assignNode->addChild(variable);
	assignNode->addChild(expr);

	return assignNode;
}


/**
 * @brief Parse a conditional expression in the program.
 *
 * @details CondExpr can only take these forms: rel_expr | '!' '(' cond_expr ')' | '(' cond_expr ')' '&&' '(' cond_expr ')' | '(' cond_expr ')' '||' '(' cond_expr ')'
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed conditional expression node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseCondExpr() {
	LexicalToken firstToken = this->tokenStream->peekToken();

	if (firstToken.isType(LexicalTokenType::NAME) || firstToken.isType(LexicalTokenType::INTEGER)) {
		return this->parseRelExpr();
	}

	std::shared_ptr<ASTNode> operationNode;
	// If of form '!' '(' cond_expr ')'.
	if (firstToken.isType(LexicalTokenType::OPERATOR_NOT)) {
		this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::OPERATOR_NOT);
		this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);

		std::shared_ptr<ASTNode> condExpr = this->parseCondExpr(); // Recursive parsing of cond_expr

		this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

		operationNode = this->createNode(ASTNodeType::NOT, this->lineManager->getLine());

		operationNode->addChild(condExpr);

		return operationNode;
	}

	// If of form  '(' cond_expr ')' '&&' '(' cond_expr ')' OR '(' cond_expr ')' '||' '(' cond_expr ')'
	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> left = this->parseCondExpr();
	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

	// Retrieve logical operator (AND, OR)
	LexicalToken logicalOperator = this->tokenStream->getNextToken();
	this->assertToken(logicalOperator, LexicalTokenType::OPERATOR_CONDITIONAL);

	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> right = this->parseCondExpr();
	this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

	ASTNodeType astType = LexicalTokenTypeMapper::lexicalToAstMap.at(logicalOperator.getTokenType());
	operationNode = this->createNode(astType, this->lineManager->getLine());

	operationNode->addChild(left);
	operationNode->addChild(right);

	return operationNode;
}

/**
 * @brief Parse a relational expression in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed relational expression node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseRelExpr() {
	std::shared_ptr<ASTNode> left = this->parseRelFactor();

	LexicalToken operatorToken = this->tokenStream->getNextToken();
	this->assertToken(operatorToken, LexicalTokenType::OPERATOR_RELATIONAL);

	std::shared_ptr<ASTNode> right = this->parseRelFactor();

	ASTNodeType astType = LexicalTokenTypeMapper::lexicalToAstMap.at(operatorToken.getTokenType());
	std::shared_ptr<ASTNode> operationNode = this->createNode(astType, this->lineManager->getLine());

	operationNode->addChild(left);
	operationNode->addChild(right);

	return operationNode;
}

/**
 * @brief Parse a relational factor in the program.
 * @details A rel_factor can be of form : var_name | const_value | expr, note that parsing a rel_factor is the same as parsing an expr.
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed relational factor node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseRelFactor() {
	return parseExpr();
}

// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/NGm3fHHy62WWafdKCc95vHpD?mode=chat
/**
 * @brief Parse a expression in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed expression node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseExpr() {
	std::shared_ptr<ASTNode> left = parseTerm();

	LexicalToken operation = this->tokenStream->peekToken();

	while (operation.isType(LexicalTokenType::OPERATOR_EXPR)) {
		this->tokenStream->getNextToken(); //consume operation token		

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

/**
 * @brief Parse a term in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed term node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseTerm() {
	std::shared_ptr<ASTNode> left = parseFactor();

	LexicalToken operation = this->tokenStream->peekToken();

	while (operation.isType(LexicalTokenType::OPERATOR_TERM)) {
		this->tokenStream->getNextToken(); //consume operation token

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

/**
 * @brief Parse a factor in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed factor node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseFactor() {
	LexicalToken nextToken = this->tokenStream->peekToken();

	if (nextToken.isType(LexicalTokenType::SYMBOL_OPEN_PAREN)) {
		this->tokenStream->getNextToken();
		std::shared_ptr<ASTNode> expr = parseExpr();
		this->assertToken(this->tokenStream->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);
		return expr;
	}

	if (nextToken.isType(LexicalTokenType::NAME)) {
		return this->parseVarName();
	}

	if (nextToken.isType(LexicalTokenType::INTEGER)) {
		return this->parseConstValue();
	}

	throw std::runtime_error("Error: SimpleParser tries to parse factor, but does not see parenthesis, name nor integer");
}

/**
 * @brief Parse a Variable Name in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed Variable Name node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseVarName() {
	LexicalToken variable = this->tokenStream->getNextToken();
	this->assertToken(variable, LexicalTokenType::NAME);
	return this->createNode(ASTNodeType::VARIABLE, this->lineManager->getLine(), variable.getValue());
}

/**
 * @brief Parse a Procedure Name in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed Procedure Name node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseProcName() {
	LexicalToken procedureName = this->tokenStream->getNextToken();
	this->assertToken(procedureName, LexicalTokenType::NAME);
	return this->createNode(ASTNodeType::VARIABLE, this->lineManager->getLine(), procedureName.getValue());
}

/**
 * @brief Parse a Constant Value in the program.
 *
 * @return std::shared_ptr<ASTNode> A smart pointer pointing to the root of the parsed Constant Value node tree.
 */
std::shared_ptr<ASTNode> SimpleParser::parseConstValue() {
	LexicalToken constant = this->tokenStream->getNextToken();
	this->assertToken(constant, LexicalTokenType::INTEGER);
	return this->createNode(ASTNodeType::CONSTANT, this->lineManager->getLine(), constant.getValue());
}
