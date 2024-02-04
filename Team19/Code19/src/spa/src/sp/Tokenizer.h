#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>

class Tokenizer {
public:
    // Token types enum
    enum class TokenType {
        KEYWORD,   // e.g., "procedure", "while", "if"
        IDENTIFIER,// e.g., "x", "Example"
        OPERATOR,  // e.g., "+", "=", "=="
        LITERAL,   // e.g., "2", "true", "false"
        SYMBOL,    // e.g., "{", "}", "(", ")"
        SEMICOLON, // ;
        UNKNOWN    // unrecognized tokens
    };

    // Token structure
    struct Token {
        TokenType type;
        std::string lexeme;
    };

    // Constructor
    Tokenizer();

    // Tokenize the input SIMPLE source code and return a vector of tokens
    std::vector<Token> tokenize(const std::string& sourceCode);

private:
    // Helper functions for tokenizing
    bool isKeyword(const std::string& word) const;
    bool isOperator(char character) const;
    bool isLiteral(const std::string& word) const;
    bool isSymbol(char character) const;
};

#endif // TOKENIZER_H
