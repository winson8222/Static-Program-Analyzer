#pragma once
#include "LexicalTokenType.h"


/**
 * @brief Represents a lexical token.
 * 
 * A lexical token is a sequence of characters that can be treated as a single unit in a program.
 */
class LexicalToken {
private:
	LexicalTokenType type;
	int lineNumber;
	int linePosition;
	std::string value;

public:
	/**
	* @brief Constructor for creating a lexical token with specified type, line number, line position, and value.
	* 
	* @param t The type of the lexical token.
	* @param lineNumber The line number associated with the lexical token (VERTICAL)
	* @param linePosition The line position associated with the lexical token (HORIZONTAL)
	* @param value The value associated with the lexical token.
	*/
	LexicalToken(LexicalTokenType t, int lineNumber, int linePosition, std::string value);

	/**
	* @brief Constructor for creating a lexical token with specified type, setting vertical/horizontal line values
	* to -1 for all, and value = ""
	*/
	LexicalToken(LexicalTokenType type);

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
	* @brief Returns the line position of the lexical token in the given file
	*/
	int getLinePosition();

	/*
	* @brief Returns the line number of the lexical token in the given file
	*/
	int getLine();

	/*
	* @brief Returns the value of the lexical token represented as a string.
	*/
	std::string getValue() const;

	/*
	* @brief Prints the lexical token to the console.
	*/
	void print();
};
