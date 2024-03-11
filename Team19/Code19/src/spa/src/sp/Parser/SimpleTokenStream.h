// ai-gen start(gpt, 1, e)
// Prompt: https://platform.openai.com/playground/p/Qttzoi5jlzeZ1ydimcPxZ7Rg?model=gpt-4&mode=chat
#pragma once

#include <memory>
#include <vector>
#include "sp/SPTokenizer/LexicalToken.h"

class SimpleTokenStream {
public:
    /**
     * Constructor takes an array of tokens
     */
    SimpleTokenStream(const std::shared_ptr<std::vector<LexicalToken>> token_ptr);

    /**
     * Returns the next token from the token stream
     */
    LexicalToken getNextToken();

    /**
     * Returns the next token from the token stream without removing it
     */
    LexicalToken peekNextToken();

    /**
     * Returns the token that is 'lookahead' tokens from the start of the token stream
     */
    LexicalToken peekToken(int lookahead);

    /**
     * Checks whether there are still tokens left in the stream
     */
    bool hasNextToken();

private:
    std::vector<LexicalToken> tokens;
    int tokenIndex;
};
