#pragma once
#include <unordered_map>
#include <string>

enum class LexicalToken {
    // Symbols
    OPEN_BRACE, CLOSE_BRACE, 
    OPEN_PAREN, CLOSE_PAREN,
    ASSIGN, 
    NOT, AND, OR, 
    GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, EQUAL_EQUAL, NOT_EQUAL,
    PLUS, MINUS, MULTIPLY, DIVIDE, MODULO, 

    // Keywords
    PROCEDURE_KEYWORD, WHILE_KEYWORD,
    IF_KEYWORD, THEN_KEYWORD, ELSE_KEYWORD, 
    READ_KEYWORD, CALL_KEYWORD, PRINT_KEYWORD, 

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
