#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>

enum class TokenType {
    NAME, INTEGER, OPERATOR, SYMBOLS, WHITESPACE
};

class Token {
public:
    TokenType type;
    int lineNumber;
    int linePosition;
    std::string name;
    std::string integer;

    Token(TokenType t) : 
        type(t), lineNumber(0), linePosition(0), name(""), integer("") {}

};

class Tokenizer {
public:
    static std::vector<Token> tokenize(std::vector<std::string> inputStream);
    static std::vector<std::string> splitLine(const std::string& content);
    static std::string readFileToString(const std::string& filename);
};
