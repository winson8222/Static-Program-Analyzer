#pragma once

#include "LexicalToken.h"

class SPTokenizer {
public:
    static std::vector<LexicalToken> tokenize(const std::string& content);
    static std::vector<std::string> splitLine(const std::string& content);

private:
    static void assertValidName(const std::string& name);
};
