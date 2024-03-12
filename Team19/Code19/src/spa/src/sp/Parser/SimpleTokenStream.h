// ai-gen start(gpt, 1, e)
// Prompt: https://platform.openai.com/playground/p/Qttzoi5jlzeZ1ydimcPxZ7Rg?model=gpt-4&mode=chat
#pragma once

#include <memory>
#include <vector>
#include "sp/SPTokenizer/LexicalToken.h"

class SimpleTokenStream {
public:
	/**
	 * @brief Constructor takes a shared pointer to an array of tokens
	 */
	SimpleTokenStream(const std::shared_ptr<std::vector<LexicalToken>> token_ptr);

	/**
	 * @brief Gets the token from the stream and advances the index by 1.
	 *
	 * @return LexicalToken The next token in the stream. Returns LexicalTokenType::NULL_TOKEN if there is no more tokens left.
	 */
	LexicalToken getNextToken();

	/**
	 * @brief Gets the token after the lookahead amount of token in the stream.
	 * @param lookahead An optional input specifying lookahead amount. Default is 1.
	 *
	 * @return LexicalToken The token that is lookahead steps ahead in the stream.
	 */
	LexicalToken peekToken(int lookahead = 1);

	/**
	 * Checks whether there are still tokens left in the stream
	 */
	bool hasTokensLeft();

private:
	std::vector<LexicalToken> tokens;
	int tokenIndex;
};
