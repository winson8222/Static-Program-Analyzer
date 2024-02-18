#include "SimpleParser.h"
#include <stdexcept>
#include <iostream>

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/cJLjmmneCEs4z6ms7ZkBSxJB?model=gpt-4&mode=chat

SimpleParser::SimpleParser(std::string filename) {
	this->tokenStream = SPTokenizer::tokenize(FileProcessor::readFileToString(filename));
	this->tokenIndex = 0;
}

std::shared_ptr<ASTNode> SimpleParser::parseProgram() {
	std::vector<std::shared_ptr<ASTNode>> procedures;

	while (this->hasTokensLeft()) {
		procedures.push_back(this->parseProcedure());
	}

	// Depending on how important the the number of lines is to the code, find out whether to further go ahead
	// with finding the number of lines.
	Program program = Program(-1, procedures);

	return program.buildTree();
}

void SimpleParser::assertToken(LexicalToken token, LexicalTokenType type) const {
	if (!token.isType(type)) {
		throw std::runtime_error("Error: Expected " + LexicalTokenTypeMapper::printType(type) + "but got " + LexicalTokenTypeMapper::printType(token.getTokenType()));
	}
}

bool SimpleParser::hasTokensLeft() const {
	return this->tokenIndex < this->tokenStream.size();
}

// Gets token, without advancing the index.
LexicalToken SimpleParser::peekNextToken() {
	if (this->hasTokensLeft()) {
		LexicalToken token = this->tokenStream[this->tokenIndex];

		if (token.isType(LexicalTokenType::WHITESPACE)) {
			this->tokenIndex++;
			return peekNextToken();
		}

		return token;
	}
	else {
		return LexicalToken(LexicalTokenType::NULL_TOKEN);
	}
}

// Gets token, and advance the index to look for the next token.
LexicalToken SimpleParser::getNextToken() {
	if (this->hasTokensLeft()) {
		LexicalToken token = this->tokenStream[this->tokenIndex];
		this->tokenIndex++;

		if (token.isType(LexicalTokenType::WHITESPACE)) {
			return getNextToken();
		}

		return token;
	}
	else {
		return LexicalToken(LexicalTokenType::NULL_TOKEN);
	}
}

// ai-gen start(gpt, 1, e)
// Prompt: https://platform.openai.com/playground/p/qA4gXcRsT0cbjv8cZDNsfqSW?mode=chat
LexicalToken SimpleParser::peekNextNextToken() {
	// Store the current index
	int originalIndex = this->tokenIndex;

	// Skip potential whitespace and get the token
	this->getNextToken();

	// Check the token after the one just returned by getNextToken()
	LexicalToken nextToken = this->peekNextToken();

	// Reset the token index to its original value
	this->tokenIndex = originalIndex;

	// Return the peeked token
	return nextToken;
}
// ai-gen end

std::shared_ptr<ASTNode> SimpleParser::parseProcedure() {
	if (!this->hasTokensLeft()) {
		throw std::runtime_error("Error: SimpleParser::parseProcedure encounter empty statement.");
	}

	LexicalToken procedureKeyword = this->getNextToken();
	this->assertToken(procedureKeyword, LexicalTokenType::KEYWORD_PROCEDURE);

	LexicalToken procedureName = this->getNextToken();
	this->assertToken(procedureName, LexicalTokenType::NAME);
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_BRACE);

	// Parse Statement Lists;
	std::shared_ptr<ASTNode> statementList = this->parseStmtLst();

	LexicalToken closeBrace = this->getNextToken();
	this->assertToken(closeBrace, LexicalTokenType::SYMBOL_CLOSE_BRACE);

	Procedure procedure = Procedure(procedureKeyword.getLine(), closeBrace.getLine(), statementList);
	return procedure.buildTree();
}

std::shared_ptr<ASTNode> SimpleParser::parseStmtLst() {
	std::vector<std::shared_ptr<ASTNode>> statements;
	int firstLine = this->peekNextToken().getLine();

	// Parse every statement until we see a closing bracket.
	while (!this->peekNextToken().isType(LexicalTokenType::SYMBOL_CLOSE_BRACE)) {
		statements.push_back(this->parseStmt());
	}

	int lastLine = this->peekNextToken().getLine();

	StmtList stmtList = StmtList(firstLine, lastLine, statements);

	return stmtList.buildTree();
}

std::shared_ptr<ASTNode> SimpleParser::parseStmt() {
	// Add parsing logic for statement
	// If next token is '=', we are assigning. Call assign.
	// Then, Check keywords read/print/call.
	// Then, check keywords while/if.
	// If dont have keyword, this is an invalid statement.
	if (!this->hasTokensLeft()) {
		throw std::runtime_error("Error: SimpleParser::parseStmt encounter empty statement.");
	}

	LexicalToken secondToken = this->peekNextNextToken();
	if (secondToken.isType(LexicalTokenType::OPERATOR_ASSIGN)) {
		return this->parseAssign();
	}

	LexicalToken firstToken = this->peekNextToken();


	if (firstToken.isType(LexicalTokenType::KEYWORD_CALL)) {
		return this->parseCall();
	}

	if (firstToken.isType(LexicalTokenType::KEYWORD_PRINT)) {
		return this->parsePrint();
	}

	if (firstToken.isType(LexicalTokenType::KEYWORD_READ)) {
		return this->parseRead();
	}

	throw std::runtime_error("Error: SimpleParser only accepts READ,CALL,PRINT statements now.");
}

std::shared_ptr<ASTNode> SimpleParser::parseRead() {
	LexicalToken keyword = this->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_READ);

	LexicalToken variable = this->getNextToken();
	this->assertToken(variable, LexicalTokenType::NAME);

	LexicalToken semicolon = this->getNextToken();
	this->assertToken(semicolon, LexicalTokenType::SYMBOL_SEMICOLON);

	ReadStmt readStmt = ReadStmt(variable, keyword.getLine(), semicolon.getLine());

	return readStmt.buildTree();
}

std::shared_ptr<ASTNode> SimpleParser::parsePrint() {
	LexicalToken keyword = this->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_PRINT);

	LexicalToken variable = this->getNextToken();
	this->assertToken(variable, LexicalTokenType::NAME);

	LexicalToken semicolon = this->getNextToken();
	this->assertToken(semicolon, LexicalTokenType::SYMBOL_SEMICOLON);

	PrintStmt printStmt = PrintStmt(variable, keyword.getLine(), semicolon.getLine());

	return printStmt.buildTree();
}

std::shared_ptr<ASTNode> SimpleParser::parseCall() {
	LexicalToken keyword = this->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_CALL);

	LexicalToken variable = this->getNextToken();
	this->assertToken(variable, LexicalTokenType::NAME);

	LexicalToken semicolon = this->getNextToken();
	this->assertToken(semicolon, LexicalTokenType::SYMBOL_SEMICOLON);

	CallStmt callStmt = CallStmt(variable, keyword.getLine(), semicolon.getLine());

	return callStmt.buildTree();
}

void SimpleParser::parseWhile() {
	// Add parsing logic for while
}

void SimpleParser::parseIf() {
	// Add parsing logic for if statement
}

std::shared_ptr<ASTNode> SimpleParser::parseAssign() {
	// Add parsing logic for assignment
	LexicalToken variable = this->getNextToken();
	this->assertToken(variable, LexicalTokenType::NAME);
	this->assertToken(this->getNextToken(), LexicalTokenType::OPERATOR_ASSIGN);

	// Comment Start:
	// To be replaced with parseExpr() and adding it as a child.
	LexicalToken expr = this->getNextToken();
	this->assertToken(expr, LexicalTokenType::INTEGER);
	// Comment end

	LexicalToken semicolon = this->getNextToken();
	this->assertToken(semicolon, LexicalTokenType::SYMBOL_SEMICOLON);

	// In the case of changing expr to parseExpr, make sure function signature also changes for expr type = std::shared_ptr<ASTNode>
	AssignStmt assignStmt = AssignStmt(variable, expr, variable.getLine(), semicolon.getLine());

	return assignStmt.buildTree();
}

// cond_expr: rel_expr
//          | ‘!’ ‘(’ cond_expr ‘)’
//          | ‘(’ cond_expr ‘)’ ‘&&’ ‘(’ cond_expr ‘)’
//          | ‘(’ cond_expr ‘)’ ‘||’ ‘(’ cond_expr ‘)’
std::shared_ptr<ASTNode> SimpleParser::parseCondExpr() {
	LexicalToken firstToken = this->peekNextToken();

	if (firstToken.isType(LexicalTokenType::NAME)) {
		return this->parseRelExpr();
	}

	if (firstToken.isType(LexicalTokenType::OPERATOR_NOT)) {
		this->getNextToken(); //consume NOT operator
		this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);

		std::shared_ptr<ASTNode> condExpr = this->parseCondExpr(); // Recursive parsing of cond_expr

		this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

		// Pass firstToken (NOT operator) and condExpr (inner condition) to NotOp constructor, and its line numbers 
		NotOp notOp = NotOp(firstToken, condExpr, firstToken.getLine(), this->peekNextToken().getLine());

		return notOp.buildTree();
	}

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);

	std::shared_ptr<ASTNode> condExpr1 = this->parseCondExpr(); // Recursive parsing of cond_expr1
	LexicalToken logicalOperator = this->getNextToken(); // Retrieve logical operator (AND, OR)

	// Must be SYMBOL and value must be either && or ||
	if (!logicalOperator.isType(LexicalTokenType::SYMBOL) ||
		(logicalOperator.getValue() != "&&" && logicalOperator.getValue() != "||")) {
		throw std::runtime_error("Expected && or || but got " + logicalOperator.getValue());
	}

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);

	std::shared_ptr<ASTNode> condExpr2 = this->parseCondExpr(); // Recursive parsing of cond_expr2

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

	if (logicalOperator.getValue() == "&&") {
		AndOp andOp = AndOp(logicalOperator, condExpr1, condExpr2, firstToken.getLine(), this->peekNextToken().getLine());
		return andOp.buildTree();
	}
	else if (logicalOperator.getValue() == "||") {
		OrOp orOp = OrOp(logicalOperator, condExpr1, condExpr2, firstToken.getLine(), this->peekNextToken().getLine());
		return orOp.buildTree();
	}

	// Default case should not be reachable
	throw std::runtime_error("Unexpected logical operator: " + logicalOperator.getValue());
}

std::shared_ptr<ASTNode> SimpleParser::parseRelExpr() {
	std::shared_ptr<ASTNode> relFactor1 = this->parseRelFactor();
	LexicalToken operatorToken = this->getNextToken();
	std::shared_ptr<ASTNode> relFactor2 = this->parseRelFactor();

	RelExpr relExpr = RelExpr(relFactor1, relFactor2, operatorToken,
		relFactor1->getFirstLine(), relFactor2->getLastLine());

	return relExpr.buildTree();
}

std::shared_ptr<ASTNode> SimpleParser::parseRelFactor() {
	LexicalToken nextToken = this->peekNextToken();

	if (nextToken.isType(LexicalTokenType::NAME)) {
		return parseVarName();
	}
	else if (nextToken.isType(LexicalTokenType::INTEGER)) {
		return parseConstValue();
	}
	else {
		return parseExpr();
	}
}

// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/NGm3fHHy62WWafdKCc95vHpD?mode=chat
std::shared_ptr<ASTNode> SimpleParser::parseExpr() {
	std::shared_ptr<ASTNode> left = parseTerm();

	LexicalToken operation = peekNextToken();

	while (operation.isType(LexicalTokenType::OPERATOR_PLUS) || operation.isType(LexicalTokenType::OPERATOR_MINUS)) {
		this->getNextToken(); //consume operation token

		auto operationNode = std::make_shared<ASTNode>();
		operationNode->setNodeType(ASTNodeType::Expr);
		operationNode->setText(operation.getValue());

		std::shared_ptr<ASTNode> right = parseTerm();

		// Create a new AST node to combine the operation with terms
		operationNode->addChild(left);
		operationNode->addChild(right);

		//Swap left operand and operation for next iteration
		left = operationNode;
		operation = peekNextToken();
	}

	return left;
}

std::shared_ptr<ASTNode> SimpleParser::parseTerm() {
	std::shared_ptr<ASTNode> left = parseFactor();

	LexicalToken operation = peekNextToken();

	while (operation.isType(LexicalTokenType::OPERATOR_MULTIPLY) || operation.isType(LexicalTokenType::OPERATOR_DIVIDE) || operation.isType(LexicalTokenType::OPERATOR_MODULO)) {
		this->getNextToken(); //consume operation token

		return std::make_shared<ASTNode>(ASTNodeType::CONSTANT, operation.getLine(), Utility::getASTNodeType(ASTNodeType::CONSTANT));
		std::shared_ptr<ASTNode> operationNode;
		if (operation.isType(LexicalTokenType::OPERATOR_MULTIPLY)) {
			operationNode = std::make_shared<ASTNode>(ASTNodeType::MULTIPLY, operation.getLine(), Utility::getASTNodeType(ASTNodeType::MULTIPLY));
		}
		else if (operation.isType(LexicalTokenType::OPERATOR_DIVIDE)) {
			operationNode = std::make_shared<ASTNode>(ASTNodeType::DIVIDE, operation.getLine(), Utility::getASTNodeType(ASTNodeType::DIVIDE));
		}
		else if (operation.isType(LexicalTokenType::OPERATOR_MODULO)) {
			operationNode = std::make_shared<ASTNode>(ASTNodeType::MODULO, operation.getLine(), Utility::getASTNodeType(ASTNodeType::MODULO));
		}
		else {
			throw std::runtime_error("Parsing Term but operator is not of the following: *, /, %");
		}

		std::shared_ptr<ASTNode> right = parseFactor();

		// Create a new AST node to combine the factor and term and add it under current operation
		operationNode->addChild(left);
		operationNode->addChild(right);

		// Swap left operand and operation for next iteration
		left = operationNode;
		operation = peekNextToken();
	}

	return left;
}
// ai-gen end

std::shared_ptr<ASTNode> SimpleParser::parseFactor() {
	LexicalToken nextToken = peekNextToken();

	if (nextToken.isType(LexicalTokenType::SYMBOL_OPEN_PAREN)) {
		this->getNextToken(); // consume open paran
		std::shared_ptr<ASTNode> expr = parseExpr();
		this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);
		return expr;
	}
	else if (nextToken.isType(LexicalTokenType::NAME)) {
		return this->parseVarName();
	}
	else if (nextToken.isType(LexicalTokenType::INTEGER)) {
		return this->parseConstValue();
	}

	// Should not come to this code.
	throw std::runtime_error("Error: SimpleParser tries to parse factor, but does not see parenthesis, name nor integer");
}

std::shared_ptr<ASTNode> SimpleParser::parseVarName() {
	LexicalToken variable = this->getNextToken();
	this->assertToken(variable, LexicalTokenType::NAME);
	return std::make_shared<ASTNode>(ASTNodeType::VARIABLE, variable.getLine(), Utility::getASTNodeType(ASTNodeType::VARIABLE));
}

std::shared_ptr<ASTNode> SimpleParser::parseProcName() {
	LexicalToken procedureName = this->getNextToken();
	this->assertToken(procedureName, LexicalTokenType::NAME);
	return std::make_shared<ASTNode>(ASTNodeType::VARIABLE, procedureName.getLine(), Utility::getASTNodeType(ASTNodeType::VARIABLE));
}

std::shared_ptr<ASTNode> SimpleParser::parseConstValue() {
	LexicalToken constant = this->getNextToken();
	this->assertToken(constant, LexicalTokenType::INTEGER);
	return std::make_shared<ASTNode>(ASTNodeType::CONSTANT, constant.getLine(), Utility::getASTNodeType(ASTNodeType::CONSTANT));
}

// ai-gen end