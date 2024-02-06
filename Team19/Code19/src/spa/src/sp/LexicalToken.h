#pragma once
#include <unordered_map>
#include <string>

enum class LexicalToken {
    // Symbols
    SYMBOL_OPEN_BRACE, SYMBOL_CLOSE_BRACE, // { and }
    SYMBOL_OPEN_PAREN, SYMBOL_CLOSE_PAREN, // ( and )
    SYMBOL_SEMICOLON, // ;
    
    // Operator
    OPERATOR_ASSIGN,    // =
    OPERATOR_NOT,       // !
    OPERATOR_AND,       // &&
    OPERATOR_OR,        // ||
    OPERATOR_GREATER, OPERATOR_GREATER_EQUAL,   // > and >=
    OPERATOR_LESS, OPERATOR_LESS_EQUAL,         // < and <=
    OPERATOR_IS_EQUAL,                          // ==
    OPERATOR_NOT_EQUAL,                         // !=
    OPERATOR_PLUS, OPERATOR_MINUS,              // + and -
    OPERATOR_MULTIPLY, OPERATOR_DIVIDE,         // * and /
    OPERATOR_MODULO,                            // %

    // Keywords
    KEYWORD_PROCEDURE,
    KEYWORD_WHILE,
    KEYWORD_IF, KEYWORD_THEN, KEYWORD_ELSE,
    KEYWORD_READ,
    KEYWORD_CALL,
    KEYWORD_PRINT,

    // General Tokens
    INTEGER, NAME, WHITESPACE, NEW_LINE,

    // Error Token
    ERROR
};

class LexicalTokenMapper {
public:
    static LexicalToken getToken(std::string str);
    static const std::unordered_map<std::string, LexicalToken> stringToTokenMap;
    static const std::unordered_map<LexicalToken, std::string> tokenToStringMap;
    static const std::unordered_map<LexicalToken, std::string> tokenToRegexMap;
};

class Token {
private:
    LexicalToken type;
    int lineNumber;
    int linePosition;
    std::string value;

public:
    Token(LexicalToken t);
    Token(LexicalToken t, int lineNumber, int linePosition, std::string value);
    void print();
};
