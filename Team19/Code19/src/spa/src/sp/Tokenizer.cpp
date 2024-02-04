#include "Tokenizer.h"
#include <iostream>
#include <sstream>

// Constructor
Tokenizer::Tokenizer() {}

// Tokenize the input SIMPLE source code and return a vector of tokens
std::vector<Tokenizer::Token> Tokenizer::tokenize(const std::string& sourceCode) {
    std::vector<Token> tokens;
    std::istringstream sourceStream(sourceCode);
    std::string token;

    while (sourceStream >> token) {
        Token t;
        if (isKeyword(token)) {
            t.type = TokenType::KEYWORD;
        }
        else if (isLiteral(token)) {
            t.type = TokenType::LITERAL;
        }
        else if (isOperator(token[0])) {
            t.type = TokenType::OPERATOR;
        }
        else if (isSymbol(token[0])) {
            t.type = TokenType::SYMBOL;
        }
        else {
            t.type = TokenType::IDENTIFIER;
        }
        t.lexeme = token;
        tokens.push_back(t);
    }
    return tokens;
}

// Helper function to check if a word is a keyword
bool Tokenizer::isKeyword(const std::string& word) const {
    // Implement your list of keywords here
    // Example: return (word == "procedure" || word == "while" || ...);
    return false; // Replace with actual logic
}

// Helper function to check if a character is an operator
bool Tokenizer::isOperator(char character) const {
    // Implement your operator check logic here
    // Example: return (character == '+' || character == '-' || ...);
    return false; // Replace with actual logic
}

// Helper function to check if a word is a literal
bool Tokenizer::isLiteral(const std::string& word) const {
    // Implement your literal check logic here
    // Example: return (isdigit(word[0]) || (word == "true" || word == "false"));
    return false; // Replace with actual logic
}

// Helper function to check if a character is a symbol
bool Tokenizer::isSymbol(char character) const {
    // Implement your symbol check logic here
    // Example: return (character == '{' || character == '}' || ...);
    return false; // Replace with actual logic
}
