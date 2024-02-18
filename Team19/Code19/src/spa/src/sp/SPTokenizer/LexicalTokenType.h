#pragma once

#include <unordered_map>
#include <string>

enum class LexicalTokenType {
    // Symbols
    SYMBOL_OPEN_BRACE, SYMBOL_CLOSE_BRACE,      // { and }
    SYMBOL_OPEN_PAREN, SYMBOL_CLOSE_PAREN,      // ( and )
    SYMBOL_SEMICOLON,                           // ;

    // Operator
    OPERATOR_ASSIGN,                            // =
    OPERATOR_NOT,                               // !
    OPERATOR_AND,                               // &&
    OPERATOR_OR,                                // ||
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


/**
* @brief a static utility class that maps back and forward token to string rerpesentation
*/
class LexicalTokenTypeMapper {
public:
    /**
    * @brief Returns the type of token (default)
    */
    static LexicalTokenType getTokenType(std::string str);

    /**
    * @brief Convert a string to a token type
    */
    static const std::unordered_map<std::string, LexicalTokenType> stringToTokenMap;

    /**
    * @brief Convert a token type to a string
    */
    static const std::unordered_map<LexicalTokenType, std::string> tokenToStringMap;

    /**
    * @brief Convert a token to its regex representations
    */
    static const std::vector<std::pair<LexicalTokenType, std::string>> tokenToRegexPairs;

    /**
    * @brief Check whether a token is a keyword
    */
    static bool isKeyword(LexicalTokenType type);

    /**
    * @brief Check whether a token is a keyword
    */
    static const std::string printType(LexicalTokenType type);
};