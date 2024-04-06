#pragma once

#include <string>
#include "LexicalTokenType.h"

/**
 * @brief Represents a lexical token.
 * 
 * A lexical token is a sequence of characters that can be treated as a single unit in a program.
 */
class LexicalToken {
private:
	LexicalTokenType type;
	std::string value;

public:
	/**
	* @brief Constructor for creating a lexical token with specified type, line number, line position, and value.
	* 
	* @param t The type of the lexical token.
	* @param value The value associated with the lexical token.
	*/
	LexicalToken(LexicalTokenType t, std::string value);

	/**
	* @brief Constructor for creating a lexical token with specified type.
	*/
	explicit LexicalToken(LexicalTokenType type);

	/*
	* @brief Default constructor for creating a null lexical token.
	*/
	LexicalToken() = default;

	/*
	* @brief Returns whether the current token is of an input given type.
	*/
	bool isType(LexicalTokenType type);

	/*
	* @brief Returns a null lexical token.
	*/
	const LexicalToken& getNullToken();

	/*
	* @brief Returns the type of the lexical token in LexicalTokenType.
	*/
	LexicalTokenType getTokenType();

	/*
	* @brief Returns the value of the lexical token represented as a string.
	*/
	std::string getValue() const;

	/**
	 * @brief Assert Token to check if the token's type matches the expected one.
	 *
	 * @param type A expected lexical token type.
	 * @throws Retrieves a runtime_error if the token's type doesn't match the expected type.
	 */
	void assertToken(LexicalTokenType type);
};
