#pragma once
#include <unordered_map>
#include <string>

enum class LexicalToken {
    // Symbols
    OPEN_BRACE, CLOSE_BRACE, 
    OPEN_PAREN, CLOSE_PAREN,
    EQUAL, 
    NOT, AND, OR, 
    GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, EQUAL_EQUAL, NOT_EQUAL,
    PLUS, MINUS, MULTIPLY, DIVIDE, MODULO, 
    PROCEDURE, WHILE,
    IF, THEN, ELSE, 
    READ, CALL, PRINT, 

    // General Tokens
    INTEGER, NAME, SPACE, NEW_LINE,

    // Error Token
    ERROR
};

class LexicalTokenMapper {
public:
    static LexicalToken getToken(std::string str);

private:
    static const std::unordered_map<std::string, LexicalToken> tokenMap;
};
