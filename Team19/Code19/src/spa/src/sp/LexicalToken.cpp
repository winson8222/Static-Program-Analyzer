#include "LexicalToken.h"
#include <iostream>
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

const std::unordered_map<LexicalToken, std::string> LexicalTokenMapper::tokenToStringMap = {
    // Symbols
    {LexicalToken::SYMBOL_OPEN_BRACE, "LEFT_BRACE"},
    {LexicalToken::SYMBOL_CLOSE_BRACE, "RIGHT_BRACE"},
    {LexicalToken::SYMBOL_OPEN_PAREN, "LEFT_PARENTHESIS"},
    {LexicalToken::SYMBOL_CLOSE_PAREN, "RIGHT_PARENTHESIS"},
    {LexicalToken::SYMBOL_SEMICOLON, "SEMICOLON"},

    // Operators
    {LexicalToken::OPERATOR_ASSIGN, "EQUAL_ASSIGNMENT"},
    {LexicalToken::OPERATOR_NOT, "NOT_EQUAL"},
    {LexicalToken::OPERATOR_AND, "LOGICAL_AND"},
    {LexicalToken::OPERATOR_OR, "LOGICAL_OR"},
    {LexicalToken::OPERATOR_GREATER, "GREATER_THAN"},
    {LexicalToken::OPERATOR_GREATER_EQUAL, "GREATER_THAN_OR_EQUAL"},
    {LexicalToken::OPERATOR_LESS, "LESS_THAN"},
    {LexicalToken::OPERATOR_LESS_EQUAL, "LESS_THAN_OR_EQUAL"},
    {LexicalToken::OPERATOR_IS_EQUAL, "EQUAL_TO"},
    {LexicalToken::OPERATOR_NOT_EQUAL, "NOT_EQUAL_TO"},
    {LexicalToken::OPERATOR_PLUS, "ADDITION"},
    {LexicalToken::OPERATOR_MINUS, "SUBTRACTION"},
    {LexicalToken::OPERATOR_MULTIPLY, "MULTIPLICATION"},
    {LexicalToken::OPERATOR_DIVIDE, "DIVISION"},
    {LexicalToken::OPERATOR_MODULO, "MODULO"},

    // Keywords
    {LexicalToken::KEYWORD_IF, "IF"},
    {LexicalToken::KEYWORD_THEN, "THEN"},
    {LexicalToken::KEYWORD_ELSE, "ELSE"},
    {LexicalToken::KEYWORD_READ, "READ"},
    {LexicalToken::KEYWORD_CALL, "CALL"},
    {LexicalToken::KEYWORD_PRINT, "PRINT"},
    {LexicalToken::KEYWORD_PRINT, "PROCEDURE"},
    {LexicalToken::KEYWORD_WHILE, "WHILE"},

    {LexicalToken::NAME, "NAMES"},
    {LexicalToken::INTEGER, "INTEGERS"},
    {LexicalToken::WHITESPACE, "WHITESPACES"},
    {LexicalToken::NEW_LINE, "NEWLINES"}

    // Add more keywords as needed
};

const std::unordered_map<LexicalToken, std::string> LexicalTokenMapper::tokenToRegexMap = {
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
    {LexicalToken::OPERATOR_PLUS, "^(\\+)"},
    {LexicalToken::OPERATOR_MINUS, "^(-)"},
    {LexicalToken::OPERATOR_MULTIPLY, "^(\\*)"},
    {LexicalToken::OPERATOR_DIVIDE, "^(\\/)"},
    {LexicalToken::OPERATOR_MODULO, "^(%)"},

    {LexicalToken::NAME, "^([a-zA-Z]\\w*)\\b"},
    {LexicalToken::INTEGER,  "^(\\d+)"},
    {LexicalToken::WHITESPACE, "^(\\s+)"}
    // Add more keywords as needed
};


LexicalToken LexicalTokenMapper::getToken(std::string str) {
    auto it = stringToTokenMap.find(str);
    if (it != stringToTokenMap.end()) {
        return it->second;
    }
    
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

SpToken::SpToken(LexicalToken t) {
    this->type = t;
}


SpToken::SpToken(LexicalToken t, int lineNumber, int linePosition, std::string value) {
    this->type = t;
    this->lineNumber = lineNumber;
    this->linePosition = linePosition;
    this->value = value;
}


void SpToken::print() {
    /*
    std::cout << "Token Type: " << LexicalTokenMapper::tokenToStringMap.find(type)->second << " ";
    std::cout << "Line Number: " << lineNumber << " ";
    std::cout << "Line Position: " << linePosition << " ";*/
    std::cout << "Value: " << std::endl;
}