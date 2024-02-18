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
		throw std::runtime_error("Error: Expected " + LexicalTokenTypeMapper::printType(type) + " but got " + LexicalTokenTypeMapper::printType(token.getTokenType()));
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
	if (!this->hasTokensLeft()) {
		throw std::runtime_error("Error: SimpleParser::parseStmt encounter empty statement.");
	}

	// If next next token is '=', we are assigning. Call assign.
	LexicalToken secondToken = this->peekNextNextToken();
	if (secondToken.isType(LexicalTokenType::OPERATOR_ASSIGN)) {
		return this->parseAssign();
	}

	LexicalToken firstToken = this->peekNextToken();


	// Then, Check keywords read/print/call.
	if (firstToken.isType(LexicalTokenType::KEYWORD_CALL)) {
		return this->parseCall();
	}

	if (firstToken.isType(LexicalTokenType::KEYWORD_PRINT)) {
		return this->parsePrint();
	}

	if (firstToken.isType(LexicalTokenType::KEYWORD_READ)) {
		return this->parseRead();
	}

	// Then, check keywords while/if.
	if (firstToken.isType(LexicalTokenType::KEYWORD_IF)) {
		return this->parseIf();
	}

	if (firstToken.isType(LexicalTokenType::KEYWORD_WHILE)) {
		return this->parseWhile();
	}


	// If dont have keyword, this is an invalid statement.
	throw std::runtime_error("Error: Invalid Statement.");
}

std::shared_ptr<ASTNode> SimpleParser::parseRead() {
	LexicalToken keyword = this->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_READ);

	std::shared_ptr<ASTNode> variable = this->parseVarName();

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_SEMICOLON);

	std::shared_ptr<ASTNode> readTree = std::make_shared<ASTNode>(
		ASTNodeType::READ, keyword.getLine(), Utility::getASTNodeType(ASTNodeType::READ)
	);

	readTree->addChild(variable);

	return readTree;
}

std::shared_ptr<ASTNode> SimpleParser::parsePrint() {
	LexicalToken keyword = this->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_PRINT);

	std::shared_ptr<ASTNode> variable = this->parseVarName();

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_SEMICOLON);

	std::shared_ptr<ASTNode> printTree = std::make_shared<ASTNode>(
		ASTNodeType::PRINT, keyword.getLine(), Utility::getASTNodeType(ASTNodeType::PRINT)
	);

	printTree->addChild(variable);

	return printTree;
}

std::shared_ptr<ASTNode> SimpleParser::parseCall() {
	LexicalToken keyword = this->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_CALL);

	std::shared_ptr<ASTNode> variable = this->parseVarName();

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_SEMICOLON);

	std::shared_ptr<ASTNode> callTree = std::make_shared<ASTNode>(
		ASTNodeType::CALL, keyword.getLine(), Utility::getASTNodeType(ASTNodeType::CALL)
	);

	callTree->addChild(variable);

	return callTree;
}

// while ( cond_expr )  { stmtLst }
std::shared_ptr<ASTNode> SimpleParser::parseWhile() {
	LexicalToken keyword = this->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_WHILE);

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> condExpr = this->parseCondExpr();
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> stmtLst = this->parseStmtLst();
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_BRACE);

	std::shared_ptr<ASTNode> whileTree = std::make_shared<ASTNode>(
		ASTNodeType::WHILE, keyword.getLine(), Utility::getASTNodeType(ASTNodeType::WHILE)
	);

	whileTree->addChild(condExpr);
	whileTree->addChild(stmtLst);

	return whileTree;
}

// if ( cond_expr) then { stmtLst } else {  stmtLst  }
std::shared_ptr<ASTNode> SimpleParser::parseIf() {
	LexicalToken keyword = this->getNextToken();
	this->assertToken(keyword, LexicalTokenType::KEYWORD_IF);

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> condExpr = this->parseCondExpr();
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

	this->assertToken(this->getNextToken(), LexicalTokenType::KEYWORD_THEN);
	
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> thenStmtLst = this->parseStmtLst();
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_BRACE);

	this->assertToken(this->getNextToken(), LexicalTokenType::KEYWORD_ELSE);

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_BRACE);
	std::shared_ptr<ASTNode> elseStmtLst = this->parseStmtLst();
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_BRACE);

	// Warning: If_ELSE_THEN ASTNodeType encountered. May need to seperate into IF, ELSE, THEN keywords.
	std::shared_ptr<ASTNode> ifTree = std::make_shared<ASTNode>(
		ASTNodeType::IF_ELSE_THEN, keyword.getLine(), Utility::getASTNodeType(ASTNodeType::IF_ELSE_THEN)
	);

	ifTree->addChild(condExpr);
	ifTree->addChild(thenStmtLst);
	ifTree->addChild(elseStmtLst);

	return ifTree;
}

std::shared_ptr<ASTNode> SimpleParser::parseAssign() {
	std::shared_ptr<ASTNode> variable = this->parseVarName();

	LexicalToken assign = this->getNextToken();
	this->assertToken(assign, LexicalTokenType::OPERATOR_ASSIGN);
	std::shared_ptr<ASTNode> assignNode = std::make_shared<ASTNode>(
		ASTNodeType::ASSIGN, assign.getLine(), Utility::getASTNodeType(ASTNodeType::ASSIGN)
	);

	std::shared_ptr<ASTNode> expr = this -> parseExpr();
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_SEMICOLON);

	assignNode->addChild(variable);
	assignNode->addChild(expr);

	return assignNode;
}

// cond_expr: rel_expr
//          | ! ( cond_expr )
//          | ( cond_expr ) && ( cond_expr )
//          | ( cond_expr ) || ( cond_expr )
std::shared_ptr<ASTNode> SimpleParser::parseCondExpr() {
	LexicalToken firstToken = this->peekNextToken();

	if (firstToken.isType(LexicalTokenType::NAME)) {
		return this->parseRelExpr();
	}

	std::shared_ptr<ASTNode> operationNode;
	// If of form ! ( cond_expr ).
	if (firstToken.isType(LexicalTokenType::OPERATOR_NOT)) {
		this->assertToken(this->getNextToken(), LexicalTokenType::OPERATOR_NOT);
		this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);

		std::shared_ptr<ASTNode> condExpr = this->parseCondExpr(); // Recursive parsing of cond_expr

		this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

		operationNode = std::make_shared<ASTNode>(ASTNodeType::NOT, firstToken.getLine(), Utility::getASTNodeType(ASTNodeType::NOT));
		operationNode->addChild(condExpr);

		return operationNode;
	}

	// If of form  ( cond_expr ) && ( cond_expr ) OR ( cond_expr ) || ( cond_expr )
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> left = this->parseCondExpr(); 
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN); 

	// Retrieve logical operator (AND, OR)
	LexicalToken logicalOperator = this->getNextToken(); 
	this->assertToken(logicalOperator, LexicalTokenType::OPERATOR_CONDITIONAL);

	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_OPEN_PAREN);
	std::shared_ptr<ASTNode> right = this->parseCondExpr(); 
	this->assertToken(this->getNextToken(), LexicalTokenType::SYMBOL_CLOSE_PAREN);

	if (logicalOperator.isType(LexicalTokenType::OPERATOR_AND)) {
		operationNode = std::make_shared<ASTNode>(ASTNodeType::AND, logicalOperator.getLine(), Utility::getASTNodeType(ASTNodeType::AND));
	}
	else if (logicalOperator.isType(LexicalTokenType::OPERATOR_OR)) {
		operationNode = std::make_shared<ASTNode>(ASTNodeType::OR, logicalOperator.getLine(), Utility::getASTNodeType(ASTNodeType::OR));
	}

	operationNode->addChild(left);
	operationNode->addChild(right);

	return operationNode;
}

//  rel_factor : var_name | const_value | expr
std::shared_ptr<ASTNode> SimpleParser::parseRelExpr() {
	std::shared_ptr<ASTNode> left = this->parseRelFactor();

	LexicalToken operatorToken = this->getNextToken();
	this->assertToken(operatorToken, LexicalTokenType::OPERATOR_RELATIONAL);

	std::shared_ptr<ASTNode> right = this->parseRelFactor();

	std::shared_ptr<ASTNode> operationNode;

	if (operatorToken.isType(LexicalTokenType::OPERATOR_GREATER)) {
		operationNode = std::make_shared<ASTNode>(ASTNodeType::GREATER, operatorToken.getLine(), Utility::getASTNodeType(ASTNodeType::GREATER));
	}
	else if (operatorToken.isType(LexicalTokenType::OPERATOR_GREATER_EQUAL)) {
		operationNode = std::make_shared<ASTNode>(ASTNodeType::GREATER_OR_EQUAL, operatorToken.getLine(), Utility::getASTNodeType(ASTNodeType::GREATER_OR_EQUAL));
	}
	else if (operatorToken.isType(LexicalTokenType::OPERATOR_LESS)) {
		operationNode = std::make_shared<ASTNode>(ASTNodeType::LESSER, operatorToken.getLine(), Utility::getASTNodeType(ASTNodeType::LESSER));
	}
	else if (operatorToken.isType(LexicalTokenType::OPERATOR_LESS_EQUAL)) {
		operationNode = std::make_shared<ASTNode>(ASTNodeType::LESSER_OR_EQUAL, operatorToken.getLine(), Utility::getASTNodeType(ASTNodeType::LESSER_OR_EQUAL));
	}
	else if (operatorToken.isType(LexicalTokenType::OPERATOR_IS_EQUAL)) {
		operationNode = std::make_shared<ASTNode>(ASTNodeType::EQUAL, operatorToken.getLine(), Utility::getASTNodeType(ASTNodeType::EQUAL));
	}
	else if (operatorToken.isType(LexicalTokenType::OPERATOR_NOT_EQUAL)) {
		operationNode = std::make_shared<ASTNode>(ASTNodeType::NOT_EQUAL, operatorToken.getLine(), Utility::getASTNodeType(ASTNodeType::NOT_EQUAL));
	}

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

	LexicalToken operation = peekNextToken();

	while (operation.isType(LexicalTokenType::OPERATOR_EXPR)) {
		this->getNextToken(); //consume operation token		

		std::shared_ptr<ASTNode> operationNode;
		if (operation.isType(LexicalTokenType::OPERATOR_PLUS)) {
			operationNode = std::make_shared<ASTNode>(ASTNodeType::ADD, operation.getLine(), Utility::getASTNodeType(ASTNodeType::ADD));
		}
		else if (operation.isType(LexicalTokenType::OPERATOR_MINUS)) {
			operationNode = std::make_shared<ASTNode>(ASTNodeType::SUBTRACT, operation.getLine(), Utility::getASTNodeType(ASTNodeType::SUBTRACT));
		}

		std::shared_ptr<ASTNode> right = parseTerm();

		// Create a new AST node to combine the expr and term and add it under current operation
		operationNode->addChild(left);
		operationNode->addChild(right);

		// Swap left operand and operation for next iteration
		left = operationNode;
		operation = peekNextToken();
	}

	return left;
}

std::shared_ptr<ASTNode> SimpleParser::parseTerm() {
	std::shared_ptr<ASTNode> left = parseFactor();

	LexicalToken operation = peekNextToken();

	while (operation.isType(LexicalTokenType::OPERATOR_TERM)) {
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
		this->getNextToken();
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
	return std::make_shared<ASTNode>(ASTNodeType::VARIABLE, variable.getLine(), variable.getValue());
}

std::shared_ptr<ASTNode> SimpleParser::parseProcName() {
	LexicalToken procedureName = this->getNextToken();
	this->assertToken(procedureName, LexicalTokenType::NAME);
	return std::make_shared<ASTNode>(ASTNodeType::VARIABLE, procedureName.getLine(), procedureName.getValue());
}

std::shared_ptr<ASTNode> SimpleParser::parseConstValue() {
	LexicalToken constant = this->getNextToken();
	this->assertToken(constant, LexicalTokenType::INTEGER);
	return std::make_shared<ASTNode>(ASTNodeType::CONSTANT, constant.getLine(), constant.getValue());
}

// ai-gen end