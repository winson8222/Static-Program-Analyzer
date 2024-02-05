#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>
#include <unordered_map>

enum class TokenType {
    NAME, INTEGER, OPERATOR_PLUS, OPERATOR_EQUAL, SEMICOLON, WHITESPACE,
    LEFT_BRACKET, RIGHT_BRACKET, KEYWORD_PROCEDURE
};

class Token {
public:
    TokenType type;
    int lineNumber;
    int linePosition;
    std::string value;

    Token(TokenType t) : 
        type(t), lineNumber(0), linePosition(0), value("") {}
    void print();
};

class Tokenizer {
public:
    static std::vector<Token> tokenize(const std::string& content);
    static std::vector<std::string> splitLine(const std::string& content);
    static std::string readFileToString(const std::string& filename);
};
