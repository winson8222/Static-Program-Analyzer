#pragma once

#include "LexicalToken.h"

class Tokenizer {
public:
    static std::vector<SpToken> tokenize(const std::string& content);
    static std::vector<std::string> splitLine(const std::string& content);
    static std::string readFileToString(const std::string& filename);
};
