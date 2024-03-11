// ai-gen start(gpt, 2, e)
// Prompt: https://platform.openai.com/playground/p/Qttzoi5jlzeZ1ydimcPxZ7Rg?model=gpt-4&mode=chat
#include "SimpleTokenStream.h"
#include <stdexcept>

SimpleTokenStream::SimpleTokenStream(const std::shared_ptr<std::vector<LexicalToken>> token_ptr) 
	: tokens(*token_ptr), tokenIndex(0) {}

/**
 * Returns the next token from the token stream
 */
LexicalToken SimpleTokenStream::getNextToken() {
	if (this->hasTokensLeft()) {
		LexicalToken token = this->tokens[this->tokenIndex];
		this->tokenIndex++;

		if (token.isType(LexicalTokenType::WHITESPACE)) {
			return getNextToken();
		}

		return token;
	}
	else {
		return LexicalToken(LexicalTokenType::NULL_TOKEN);
	}
}

/**
 * Returns the token that is 'lookahead' tokens from the start of the token stream
 */
LexicalToken SimpleTokenStream::peekToken(int lookahead) {
	if (lookahead < 0) {
		throw std::runtime_error("Error: PeekToken cannot have negative lookahead value");
	}

	// Store the current index
	int originalIndex = this->tokenIndex;

	LexicalToken resultToken;
	for (int i = 0; i < lookahead; i++) {
		resultToken = this->getNextToken();
	}

	this->tokenIndex = originalIndex;

	return resultToken;
}

bool SimpleTokenStream::hasTokensLeft() {
	return this->tokenIndex < static_cast<int>(this->tokens.size());
}
// ai-gen end