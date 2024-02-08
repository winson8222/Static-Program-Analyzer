#include "LexicalToken.h"
#include <iostream>

LexicalToken::LexicalToken(LexicalTokenType t, int lineNumber, int linePosition, std::string value) {
    this->type = t;
    this->lineNumber = lineNumber;
    this->linePosition = linePosition;
    this->value = value;
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
    std::cout << "Value: " << value << std::endl;
}