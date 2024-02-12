#include "SimpleParser.h"
#include <stdexcept>
#include <iostream>

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/cJLjmmneCEs4z6ms7ZkBSxJB?model=gpt-4&mode=chat


SimpleParser::SimpleParser(std::string filename) {
	this->tokenStream = Tokenizer::tokenize(Tokenizer::readFileToString(filename));
	this->tokenIndex = 0;
}

void SimpleParser::parseProgram() {
	while (this->hasTokensLeft()) {
		parseProcedure();
	}
}

bool SimpleParser::hasTokensLeft() const {
	return this->tokenIndex < this->tokenStream.size();
}

// Gets token, without advancing the index.
LexicalToken SimpleParser::peekToken() const {
	if (this->hasTokensLeft()) {
		return this->tokenStream[this->tokenIndex];
	}
	else {
		return LexicalToken(LexicalTokenType::NULL_TOKEN);
	}
}

// Gets token, and advance the index to look for the next token.
LexicalToken SimpleParser::getToken() {
	if (this->hasTokensLeft()) {
		LexicalToken token = this->tokenStream[this->tokenIndex];
		this->tokenIndex++;
		return token;
	}
	else {
		return LexicalToken(LexicalTokenType::NULL_TOKEN);
	}
}

void SimpleParser::assertToken(LexicalToken token, LexicalTokenType type) const {
	if (token.getTokenType() != type) {
		throw std::runtime_error("Error: Invalid SIMPLE syntax.");
	}
}


void SimpleParser::parseProcedure() {
	if (!this->hasTokensLeft()) {
		return;
	}

	LexicalToken procedureKeyword = this->getToken();

}

void SimpleParser::parseStmtLst() {
	// Add parsing logic for statement list
	// Parse every statement until we see a closing bracket.
}

void SimpleParser::parseStmt() {
	// Add parsing logic for statement
	// If next token is '=', we are assigning. Call assign.
	// Then, Check keywords read/print/call.
	// Then, check keywords while/if.
	// If dont have keyword, this is an invalid statement.
	if (!this->hasTokensLeft()) {
		return;
	}

	LexicalToken firstToken = this->peekToken();
	if (firstToken.getTokenType() == LexicalTokenType::KEYWORD_CALL) {
		this->parseCall();
	}

	if (firstToken.getTokenType() == LexicalTokenType::KEYWORD_PRINT) {
		this->parsePrint();
	}

	if (firstToken.getTokenType() == LexicalTokenType::KEYWORD_READ) {
		this->parseRead();
	}

}

ReadStmt SimpleParser::parseRead() {
	LexicalToken keyword = this->getToken();

	if (keyword.getTokenType() != LexicalTokenType::KEYWORD_READ) {
		throw std::runtime_error("Error: Invalid SIMPLE syntax.");
	}

	LexicalToken variable = this->getToken();

	if (variable.getTokenType() != LexicalTokenType::NAME) {
		throw std::runtime_error("Error: Invalid SIMPLE syntax.");
	}

	LexicalToken semicolon = this->getToken();

	if (semicolon.getTokenType() != LexicalTokenType::SYMBOL_SEMICOLON) {
		throw std::runtime_error("Error: Invalid SIMPLE syntax.");
	}

	return ReadStmt(variable, keyword.getLine(), semicolon.getLine());

	// Add the readStmt to the Tree.
}

PrintStmt SimpleParser::parsePrint() {
	LexicalToken keyword = this->getToken();

	if (keyword.getTokenType() != LexicalTokenType::KEYWORD_PRINT) {
		throw std::runtime_error("Error: Invalid SIMPLE syntax.");
	}

	LexicalToken variable = this->getToken();

	if (variable.getTokenType() != LexicalTokenType::NAME) {
		throw std::runtime_error("Error: Invalid SIMPLE syntax.");
	}

	LexicalToken semicolon = this->getToken();

	if (semicolon.getTokenType() != LexicalTokenType::SYMBOL_SEMICOLON) {
		throw std::runtime_error("Error: Invalid SIMPLE syntax.");
	}

	return PrintStmt(variable, keyword.getLine(), semicolon.getLine());

	// Add the printStmt to the Tree.
}

// To change to void later when building trees.
CallStmt SimpleParser::parseCall() {
	LexicalToken keyword = this->getToken();

	if (keyword.getTokenType() != LexicalTokenType::KEYWORD_CALL) {
		throw std::runtime_error("Error: Invalid SIMPLE syntax.");
	}

	LexicalToken variable = this->getToken();

	if (variable.getTokenType() != LexicalTokenType::NAME) {
		throw std::runtime_error("Error: Invalid SIMPLE syntax.");
	}

	LexicalToken semicolon = this->getToken();

	if (semicolon.getTokenType() != LexicalTokenType::SYMBOL_SEMICOLON) {
		throw std::runtime_error("Error: Invalid SIMPLE syntax.");
	}

	return CallStmt(variable, keyword.getLine(), semicolon.getLine());

	// Add the callStmt to the Tree.
}

void SimpleParser::parseWhile() {
	// Add parsing logic for while
}

void SimpleParser::parseIf() {
	// Add parsing logic for if statement
}

void SimpleParser::parseAssign() {
	// Add parsing logic for assignment
}

void SimpleParser::parseCondExpr() {
	// Add parsing logic for condition expression
}

void SimpleParser::parseRelExpr() {
	// Add parsing logic for relational expression
}

void SimpleParser::parseRelFactor() {
	// Add parsing logic for relational factor (variable name or constant value or expression)
}

void SimpleParser::parseExpr() {
	// Add parsing logic for expression (term or expression "+" term or expression "-" term)
}

void SimpleParser::parseTerm() {
	// Add parsing logic for term (factor or term "*" factor or term "/" factor or term "%" factor)
}

void SimpleParser::parseFactor() {
	// Add parsing logic for factor (variable name or constant value or "(" expr ")")
}

void SimpleParser::parseVarName() {
	// Add parsing logic for variable name
}

void SimpleParser::parseProcName() {
	// Add parsing logic for procedure name
}

void SimpleParser::parseConstValue() {
	// Add parsing logic for constant value parsing
}
// ai-gen end