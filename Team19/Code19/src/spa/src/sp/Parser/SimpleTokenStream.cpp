// ai-gen start(gpt, 2, e)
// Prompt: https://platform.openai.com/playground/p/Qttzoi5jlzeZ1ydimcPxZ7Rg?model=gpt-4&mode=chat
#include "SimpleTokenStream.h"
#include <stdexcept>

SimpleTokenStream::SimpleTokenStream(const std::shared_ptr<std::vector<LexicalToken>> token_ptr) 
	: tokens(*token_ptr), tokenIndex(0) {}


LexicalToken SimpleTokenStream::getNextToken() {
	if (this->hasNext()) {
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

LexicalToken SimpleTokenStream::peekToken(int lookahead) {
	if (lookahead <= 0) {
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

bool SimpleTokenStream::hasNext() {
	return this->tokenIndex < static_cast<int>(this->tokens.size());
}
// ai-gen end

bool SimpleTokenStream::hasTokensLeft() {
	LexicalToken nextToken = this->peekToken();
	return !nextToken.isType(LexicalTokenType::NULL_TOKEN);
}

void SimpleTokenStream::popAndAssertToken(LexicalTokenType type) {
	LexicalToken nextToken = this->getNextToken();
	nextToken.assertToken(type);
}
