#pragma once

#include "LexicalToken.h"


/**
 * @brief Represents a tokenizer which takes in a string and tokenizes it.
 */
class SPTokenizer {
public:
    /**
    * @brief Tokenizes the content of a string and returns a vector of lexical tokens.
    * 
    * @param content The content to be tokenized.
    * @return A vector of lexical tokens.
    */
    static std::vector<LexicalToken> tokenize(const std::string& content);

    /**
    * Split a line (of multiple lines) into a vector of strings.
    */
    static std::vector<std::string> splitLine(const std::string& content);

private:
    static void assertValidToken(LexicalTokenType type, const std::string& name);
    static void handleKeywordConflict(LexicalTokenType& type, bool& isPreviousTokenKeyword);
};
