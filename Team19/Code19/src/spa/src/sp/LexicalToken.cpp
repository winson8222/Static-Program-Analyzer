#include "LexicalToken.h"
#include <iostream>



LexicalToken::LexicalToken(LexicalTokenType type) {
    this->type = type;
    this->lineNumber = NULL;
    this->linePosition = NULL;
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

std::string LexicalToken::getValue() {
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

void LexicalToken::print() {
    std::cout << "Token Type: " << LexicalTokenTypeMapper::tokenToStringMap.find(type)->second << " ";
    std::cout << "Line Number: " << lineNumber << " ";
    std::cout << "Line Position: " << linePosition << " ";
    std::cout << "Value: " << std::endl;
}