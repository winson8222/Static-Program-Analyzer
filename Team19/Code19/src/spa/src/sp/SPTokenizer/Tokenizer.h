#pragma once

#include "LexicalToken.h"

class SPTokenizer {
public:
    static std::vector<LexicalToken> tokenize(const std::string& content);
    static std::vector<std::string> splitLine(const std::string& content);
    static std::string readFileToString(const std::string& filename);
};
