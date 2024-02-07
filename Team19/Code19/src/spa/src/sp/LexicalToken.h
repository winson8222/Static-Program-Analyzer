#pragma once
#include "LexicalTokenType.h"

class LexicalToken {
private:
    LexicalTokenType type;
    int lineNumber;
    int linePosition;
    std::string value;

public:
    LexicalToken(LexicalTokenType t);
    LexicalToken(LexicalTokenType t, int lineNumber, int linePosition, std::string value);
    LexicalTokenType getTokenType();
    void print();
};
