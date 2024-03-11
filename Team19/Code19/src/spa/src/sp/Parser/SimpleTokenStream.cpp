// ai-gen start(gpt, 2, e)
// Prompt: https://platform.openai.com/playground/p/Qttzoi5jlzeZ1ydimcPxZ7Rg?model=gpt-4&mode=chat
#include "SimpleTokenStream.h"

SimpleTokenStream::SimpleTokenStream(const std::shared_ptr<std::vector<LexicalToken>> token_ptr) 
	: tokens(*token_ptr), tokenIndex(0) {}

/**
 * Returns the next token from the token stream
 */
LexicalToken SimpleTokenStream::getNextToken() {
	if (!hasNextToken()) {
		errorFlag = true;
		errorMessage = "No more tokens left";
		return LexicalToken(); // return a null token
	}
	return tokens[tokenIndex++];
}

/**
 * Returns the next token from the token stream without removing it
 */
LexicalToken SimpleTokenStream::peekNextToken() {
	if (!hasNextToken()) {
		errorFlag = true;
		errorMessage = "No more tokens left";
		return LexicalToken(); // return a null token
	}
	return tokens[tokenIndex];
}

/**
 * Returns the token that is 'lookahead' tokens from the start of the token stream
 */
LexicalToken SimpleTokenStream::peekToken(int lookahead) {
	if (!hasToken(lookahead)) {
		errorFlag = true;
		errorMessage = "No more tokens left";
		return LexicalToken(); // return a null token
	}
	return tokens[tokenIndex + lookahead];
}

/**
 * Checks whether there are still tokens left in the stream
 */
bool SimpleTokenStream::hasNextToken() {
	return tokenIndex < static_cast<int>(tokens.size());
}

/**
 * Checks whether there are at least 'lookahead' tokens from the start of the token stream
 */
bool SimpleTokenStream::hasToken(int lookahead) {
	return (tokenIndex + lookahead) < static_cast<int>(tokens.size());
}

/**
 * Resets the token stream to the beginning
 */
void SimpleTokenStream::reset() {
	tokenIndex = 0;
	errorFlag = false;
	errorMessage.clear();
}

/**
 * Indicates whether an error has occurred during the token stream processing
 */
bool SimpleTokenStream::errorOccurred() {
	return errorFlag;
}

/**
 * Returns the error message, only valid when errorOccurred() returns true
 */
std::string SimpleTokenStream::getErrorMessage() {
	return errorMessage;
}
// ai-gen end