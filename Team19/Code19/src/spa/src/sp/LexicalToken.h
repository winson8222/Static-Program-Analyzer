#pragma once
#include "LexicalTokenType.h"

class LexicalToken {
private:
    LexicalTokenType type;
    int lineNumber;
    int linePosition;
    std::string value;

public:
    LexicalToken(LexicalTokenType t, int lineNumber, int linePosition, std::string value);
    LexicalToken(LexicalTokenType type);
    LexicalToken() = default;
    
    const LexicalToken& LexicalToken::getNullToken();
    LexicalTokenType getTokenType();
    int getLinePosition();
    int getLine();
    std::string getValue();
    void print();
};
