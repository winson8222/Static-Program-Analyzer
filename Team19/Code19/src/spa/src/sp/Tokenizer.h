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
    LEFT_BRACKET, RIGHT_BRACKET
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
    void print();
};

class Tokenizer {
public:
    static std::vector<Token> tokenize(const std::string& content);
    static std::vector<std::string> splitLine(const std::string& content);
    static std::string readFileToString(const std::string& filename);
};
