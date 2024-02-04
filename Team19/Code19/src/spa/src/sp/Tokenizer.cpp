#include "Tokenizer.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <stdexcept>


std::vector<std::string> Tokenizer::splitLine(std::istream& stream) {
    std::vector<std::string> result;
    std::string line;
    while (std::getline(stream, line)) {
        result.push_back(line);
    }
    return result;
}

Token::Token(TokenType t)
    : type(t), lineNumber(0), linePosition(0), name(""), integer("") {}

TokenType Token::getType() const {
    return type;
}

int Token::getLineNumber() const {
    return lineNumber;
}

int Token::getLinePosition() const {
    return linePosition;
}

const std::string& Token::getName() const {
    return name;
}

const std::string& Token::getInteger() const {
    return integer;
}

std::vector<Token> Tokenizer::tokenize(std::istream& stream) {
    std::vector<Token> result;

    return result;
}
