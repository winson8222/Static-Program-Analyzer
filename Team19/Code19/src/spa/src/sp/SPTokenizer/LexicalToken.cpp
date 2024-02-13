#include "LexicalToken.h"
#include <iostream>

LexicalToken::LexicalToken(LexicalTokenType type) {
	this->type = type;
	this->lineNumber = -1;
	this->linePosition = -1;
	this->value = "";
}

LexicalToken::LexicalToken(LexicalTokenType t, int lineNumber, int linePosition, std::string value) {
	this->type = t;
	this->lineNumber = lineNumber;
	this->linePosition = linePosition;
	this->value = value;
}

const LexicalToken& LexicalToken::getNullToken() {
	static const LexicalToken nullToken(LexicalTokenType::NULL_TOKEN);
	return nullToken;
}

std::string LexicalToken::getValue() const {
	return this->value;
}

int LexicalToken::getLinePosition() {
	return this->linePosition;
}

LexicalTokenType LexicalToken::getTokenType() {
	return this->type;
}

int LexicalToken::getLine() {
	return this->lineNumber;
}

bool LexicalToken::isType(LexicalTokenType type) {
	switch (this->getTokenType()) {
	case LexicalTokenType::KEYWORD_PROCEDURE:
	case LexicalTokenType::KEYWORD_WHILE:
	case LexicalTokenType::KEYWORD_IF:
	case LexicalTokenType::KEYWORD_THEN:
	case LexicalTokenType::KEYWORD_ELSE:
	case LexicalTokenType::KEYWORD_READ:
	case LexicalTokenType::KEYWORD_CALL:
	case LexicalTokenType::KEYWORD_PRINT:
		if (type == LexicalTokenType::NAME) {
			return true;
		}
		[[fallthrough]];
	default:
		return this->getTokenType() == type;
	}
}

void LexicalToken::print() {
	std::cout << "Token Type: " << LexicalTokenTypeMapper::tokenToStringMap.find(type)->second << " ";
	std::cout << "Line Number: " << lineNumber << " ";
	std::cout << "Line Position: " << linePosition << " ";
	std::cout << "Value: " << std::endl;
}