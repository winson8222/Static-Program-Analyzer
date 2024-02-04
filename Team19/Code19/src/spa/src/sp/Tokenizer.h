#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>


enum class TokenType {
    NAME, INTEGER, OPERATOR, COMPARATOR, SPECIAL, WHITESPACE
};

class Token {
private:
    TokenType type;
    int lineNumber;
    int linePosition;
    std::string name;
    std::string integer;

    Token() = delete;

public:
    Token(TokenType t) : 
        type(t), lineNumber(0), linePosition(0), name(""), integer("") {}

    TokenType getType() const;
    int getLineNumber() const;
    int getLinePosition() const;
    const std::string& getName() const;
    const std::string& getInteger() const;
};

class Tokenizer {
public:
    static std::vector<Token> tokenize(std::istream& stream);
    static std::vector<std::string> splitLine(std::istream& stream);
};
