#pragma once

#include <unordered_map>
#include <string>

enum class LexicalTokenType {
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
    ERROR,

    // Null Token
    NULL_TOKEN
};

class LexicalTokenTypeMapper {
public:
    static LexicalTokenType getTokenType(std::string str);
    static const std::unordered_map<std::string, LexicalTokenType> stringToTokenMap;
    static const std::unordered_map<LexicalTokenType, std::string> tokenToStringMap;
    static const std::vector<std::pair<LexicalTokenType, std::string>> tokenToRegexPairs;
};