#include "LexicalToken.h"
#include <regex>

const std::unordered_map<std::string, LexicalToken> LexicalTokenMapper::stringToTokenMap = {
    // Symbols
    {"{", LexicalToken::SYMBOL_OPEN_BRACE},
    {"}", LexicalToken::SYMBOL_CLOSE_BRACE},
    {"(", LexicalToken::SYMBOL_OPEN_PAREN},
    {")", LexicalToken::SYMBOL_CLOSE_PAREN},
    {";", LexicalToken::SYMBOL_SEMICOLON},

    // Operators
    {"=", LexicalToken::OPERATOR_ASSIGN},
    {"!", LexicalToken::OPERATOR_NOT},
    {"&&", LexicalToken::OPERATOR_AND},
    {"||", LexicalToken::OPERATOR_OR},
    {">", LexicalToken::OPERATOR_GREATER},
    {">=", LexicalToken::OPERATOR_GREATER_EQUAL},
    {"<", LexicalToken::OPERATOR_LESS},
    {"<=", LexicalToken::OPERATOR_LESS_EQUAL},
    {"==", LexicalToken::OPERATOR_IS_EQUAL},
    {"!=", LexicalToken::OPERATOR_NOT_EQUAL},
    {"+", LexicalToken::OPERATOR_PLUS},
    {"-", LexicalToken::OPERATOR_MINUS},
    {"*", LexicalToken::OPERATOR_MULTIPLY},
    {"/", LexicalToken::OPERATOR_DIVIDE},
    {"%", LexicalToken::OPERATOR_MODULO},

    // Keywords
    {"if", LexicalToken::KEYWORD_IF},
    {"then", LexicalToken::KEYWORD_THEN},
    {"else", LexicalToken::KEYWORD_ELSE},
    {"read", LexicalToken::KEYWORD_READ},
    {"call", LexicalToken::KEYWORD_CALL},
    {"print", LexicalToken::KEYWORD_PRINT},
    {"procedure", LexicalToken::KEYWORD_PRINT},
    {"while", LexicalToken::KEYWORD_WHILE},

    {" ", LexicalToken::WHITESPACE},
    {"\n", LexicalToken::NEW_LINE}
    // Add more keywords as needed
};

const std::unordered_map<LexicalToken, std::string> tokenToStringMap = {
    // Symbols
    {LexicalToken::SYMBOL_OPEN_BRACE, "{"},
    {LexicalToken::SYMBOL_CLOSE_BRACE, "}"},
    {LexicalToken::SYMBOL_OPEN_PAREN, "("},
    {LexicalToken::SYMBOL_CLOSE_PAREN, ")"},
    {LexicalToken::SYMBOL_SEMICOLON, ";"},

    // Operators
    {LexicalToken::OPERATOR_ASSIGN, "="},
    {LexicalToken::OPERATOR_NOT, "!"},
    {LexicalToken::OPERATOR_AND, "&&"},
    {LexicalToken::OPERATOR_OR, "||"},
    {LexicalToken::OPERATOR_GREATER, ">"},
    {LexicalToken::OPERATOR_GREATER_EQUAL, ">="},
    {LexicalToken::OPERATOR_LESS, "<"},
    {LexicalToken::OPERATOR_LESS_EQUAL, "<="},
    {LexicalToken::OPERATOR_IS_EQUAL, "=="},
    {LexicalToken::OPERATOR_NOT_EQUAL, "!="},
    {LexicalToken::OPERATOR_PLUS, "+"},
    {LexicalToken::OPERATOR_MINUS, "-"},
    {LexicalToken::OPERATOR_MULTIPLY, "*"},
    {LexicalToken::OPERATOR_DIVIDE, "/"},
    {LexicalToken::OPERATOR_MODULO, "%"},

    // Keywords
    {LexicalToken::KEYWORD_IF, "if"},
    {LexicalToken::KEYWORD_THEN, "then"},
    {LexicalToken::KEYWORD_ELSE, "else"},
    {LexicalToken::KEYWORD_READ, "read"},
    {LexicalToken::KEYWORD_CALL, "call"},
    {LexicalToken::KEYWORD_PRINT, "print"},
    {LexicalToken::KEYWORD_PRINT, "procedure"},
    {LexicalToken::KEYWORD_WHILE, "while"},

    {LexicalToken::WHITESPACE, "whitespaces"},
    {LexicalToken::NEW_LINE, "newlines"}
    // Add more keywords as needed
};

const std::unordered_map<LexicalToken, std::string> tokenToRegexMap = {
    // Symbols
    {LexicalToken::SYMBOL_OPEN_BRACE, "^(\\{)"},
    {LexicalToken::SYMBOL_CLOSE_BRACE, "^(\\})"},
    {LexicalToken::SYMBOL_OPEN_PAREN, "^(\\()"},
    {LexicalToken::SYMBOL_CLOSE_PAREN, "^(\\))"},
    {LexicalToken::SYMBOL_SEMICOLON, "^(;)"},
    {LexicalToken::OPERATOR_ASSIGN, "^(=)"},
    {LexicalToken::OPERATOR_NOT, "^(!)"},
    {LexicalToken::OPERATOR_AND, "^(&&)"},
    {LexicalToken::OPERATOR_OR, "^(\\|\\|)"},
    {LexicalToken::OPERATOR_GREATER, "^(>)"},
    {LexicalToken::OPERATOR_GREATER_EQUAL, "^(>=)"},
    {LexicalToken::OPERATOR_LESS, "^(<)"},
    {LexicalToken::OPERATOR_LESS_EQUAL, "^(<=)"},
    {LexicalToken::OPERATOR_IS_EQUAL, "^(==)"},
    {LexicalToken::OPERATOR_NOT_EQUAL, "^(!=)"},
    {LexicalToken::OPERATOR_PLUS, "^(+)"},
    {LexicalToken::OPERATOR_MINUS, "^(-)"},
    {LexicalToken::OPERATOR_MULTIPLY, "^(*)"},
    {LexicalToken::OPERATOR_DIVIDE, "^(/)"},
    {LexicalToken::OPERATOR_MODULO, "^(%)"},

    {LexicalToken::NAME, "^([a-zA-Z][a-zA-Z0-9]*)"},
    {LexicalToken::INTEGER, "^(\d+)"},
    {LexicalToken::WHITESPACE, "^(\\s+)"}
    // Add more keywords as needed
};


LexicalToken LexicalTokenMapper::getToken(std::string str) {
    auto it = stringToTokenMap.find(str);
    if (it != stringToTokenMap.end()) {
        return it->second;
    }
    
    // std::string regexName = LexicalTokenMapper::tokenToRegexMap.find(LexicalToken::NAME)->second;
    // std::string regexInt = LexicalTokenMapper::tokenToRegexMap.find(LexicalToken::INTEGER)->second;

    // Check for valid integer pattern (\d+)
    if (std::regex_match(str, std::regex(R"(\d+)"))) {
        return LexicalToken::INTEGER;
    }

    // Check for valid name pattern ([a-zA-Z][a-zA-Z0-9]*)
    if (std::regex_match(str, std::regex(R"([a-zA-Z][a-zA-Z0-9]*)"))) {
        return LexicalToken::NAME;
    }

    return LexicalToken::ERROR;
}
