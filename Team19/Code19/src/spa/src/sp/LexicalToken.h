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
    LexicalTokenType getTokenType();
    int getLine();
    void print();
};
