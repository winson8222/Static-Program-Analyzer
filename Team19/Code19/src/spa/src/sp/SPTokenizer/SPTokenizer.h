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

	/*
	* @brief Check and assert that a string valued token is valid.
	* @param type The type of the token to be checked.
	* @param name The name of the token to be checked.
	* @throws std::invalid_argument if the token is invalid - which happens if it
	* fails the regex check - having only alphanumeric characters and first character being a letter.
	*/
	static void assertValidToken(LexicalTokenType type, const std::string& name);
};
