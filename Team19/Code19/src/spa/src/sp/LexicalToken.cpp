#include "LexicalToken.h"
#include <regex>

const std::unordered_map<std::string, LexicalToken> LexicalTokenMapper::tokenMap = {
    // Symbols
    {"{", LexicalToken::OPEN_BRACE},
    {"}", LexicalToken::CLOSE_BRACE},
    {"(", LexicalToken::OPEN_PAREN},
    {")", LexicalToken::CLOSE_PAREN},
    {"=", LexicalToken::ASSIGN},
    {"!", LexicalToken::NOT},
    {"&&", LexicalToken::AND},
    {"||", LexicalToken::OR},
    {">", LexicalToken::GREATER},
    {">=", LexicalToken::GREATER_EQUAL},
    {"<", LexicalToken::LESS},
    {"<=", LexicalToken::LESS_EQUAL},
    {"==", LexicalToken::EQUAL_EQUAL},
    {"!=", LexicalToken::NOT_EQUAL},
    {"+", LexicalToken::PLUS},
    {"-", LexicalToken::MINUS},
    {"*", LexicalToken::MULTIPLY},
    {"/", LexicalToken::DIVIDE},
    {"%", LexicalToken::MODULO},

    // Keywords
    {"if", LexicalToken::IF_KEYWORD},
    {"then", LexicalToken::THEN_KEYWORD},
    {"else", LexicalToken::ELSE_KEYWORD},
    {"read", LexicalToken::READ_KEYWORD},
    {"call", LexicalToken::CALL_KEYWORD},
    {"print", LexicalToken::PRINT_KEYWORD},
    {"procedure", LexicalToken::PROCEDURE_KEYWORD},
    {"while", LexicalToken::WHILE_KEYWORD},

    {" ", LexicalToken::SPACE},
    {"\n", LexicalToken::NEW_LINE}
    // Add more keywords as needed
};


LexicalToken LexicalTokenMapper::getToken(std::string str) {
    auto it = tokenMap.find(str);
    if (it != tokenMap.end()) {
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
