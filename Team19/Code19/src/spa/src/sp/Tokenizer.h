#pragma once

#include "LexicalToken.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <regex>
#include <string>
#include <vector>
#include <unordered_map>


class Tokenizer {
public:
    static std::vector<SpToken> tokenize(const std::string& content);
    static std::vector<std::string> splitLine(const std::string& content);
    static std::string readFileToString(const std::string& filename);
};
