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

// prototype for matching rules
std::unordered_map<TokenType, std::string> rules = {
        { TokenType::NAME, "^([a-zA-Z]\\w*)\\b" },
        { TokenType::INTEGER, "^(\\d+)" },
        { TokenType::OPERATOR_PLUS, "^(\\+)" },
        { TokenType::OPERATOR_EQUAL, "^(=)" },
        { TokenType::SEMICOLON, "^(;)" },
        { TokenType::WHITESPACE, "^(\\s+)" },
        { TokenType::LEFT_BRACKET, "^(\\{)" },
        { TokenType::RIGHT_BRACKET, "^(\\})" }
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
