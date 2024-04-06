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
	explicit SimpleTokenStream(const std::shared_ptr<std::vector<LexicalToken>> token_ptr);

	/**
	 * @brief Gets the token after the lookahead amount of token in the stream.
	 * @param lookahead An optional input specifying lookahead amount. Default is 1.
	 *
	 * @return LexicalToken The token that is lookahead steps ahead in the stream.
	 */
	LexicalToken peekToken(int lookahead = 1);

	/**
	 * @brief Checks whether there are still tokens left in the stream.
	 * 
	 * @return A boolean signifying if there is still tokens in the stream.
	 */
	bool hasTokensLeft();

	/**
	* @brief Advances the index by 1, and check if it matches the given token type.
	* 
	* @throws An error if the next token does not match the given type.
	*/
	void popAndAssertToken(LexicalTokenType type, int line);

private:
	std::vector<LexicalToken> tokens;
	int tokenIndex;
	LexicalToken getNextToken();
	bool hasNext();
};
