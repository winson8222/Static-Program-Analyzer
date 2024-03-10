#pragma once

// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/TSrBejqZDhzJU0nYh4NsepD0
#include "SimpleParser.h"
#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SPTokenizer/FileProcessor.h"
#include <memory>

/**
* @brief Facade class to handle input Simple program, and generate its abstract syntax tree (AST) representation.
*/
class SimpleParserFacade {
private:
	std::unique_ptr<SimpleParser> parser;

public:
	/**
	* @brief Constructs a SimpleParserFacade object.
	*
	* @param filename The filename of the file containing the SIMPLE source code.
	*/
	SimpleParserFacade(const std::string& filename);

	/**
	* @brief Parses the program file and returns AST representation.
	*
	* @return A shared pointer to the root of the AST representing the parsed program.
	*/
	std::shared_ptr<ASTNode> parse();
};
// ai-gen end