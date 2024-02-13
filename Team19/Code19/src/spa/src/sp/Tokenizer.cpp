#include "../../spa/src/sp/Tokenizer.h"
#include "LexicalToken.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

/** Splits the text file into a array of strings, with each element representing a line of text.
 *  Returns: A vector of size equal to the number of lines in the input content.
 */
std::vector<std::string> Tokenizer::splitLine(const std::string& content) {
	std::vector<std::string> result;
	std::istringstream stream(content); // Create a stringstream from the content
	std::string line;

	while (std::getline(stream, line)) {
		result.push_back(line);
	}

	return result;
}

std::vector<LexicalToken> Tokenizer::tokenize(const std::string& content) {
	std::vector<LexicalToken> results;
	std::vector<std::string> lines = Tokenizer::splitLine(content);
	int numberOfLines = static_cast<int>(lines.size());

	for (int lineNumber = 1; lineNumber <= numberOfLines; lineNumber++) {
		std::string line = lines[lineNumber - 1];
		std::string originalLine = line.substr();

		while (!line.empty()) {
			bool matchedSomething = false;
			for (auto const& rule : LexicalTokenTypeMapper::tokenToRegexPairs) {
				std::smatch match;
				if (std::regex_search(line, match, std::regex(rule.second))) {
					std::cout << match.str() << std::endl;
					LexicalToken t(rule.first, lineNumber, (int)(originalLine.size() - line.size()), match.str());

					if (rule.first != LexicalTokenType::WHITESPACE) {
						results.push_back(t);
					}

					matchedSomething = true;
					line = line.substr(match.str().size());
					break;
				}
			}

			// Buggy
			if (!matchedSomething) {
				throw std::runtime_error("Error: Invalid SIMPLE syntax.");
			}
		}

		if (lineNumber != lines.size()) {
			LexicalToken newLine(LexicalTokenType::WHITESPACE, lineNumber, -1, "new line");
			results.push_back(newLine);
		}
	}

	for (auto it : results) {
		it.print();
	}

	return results;
}


std::string Tokenizer::readFileToString(const std::string& filename) {
	// Create an input file stream to read the file
	std::ifstream inputFile(filename);

	// Check if the file was opened successfully
	if (!inputFile.is_open()) {
		throw std::runtime_error("Error: Unable to open the input file.");
	}

	std::stringstream buffer;
	buffer << inputFile.rdbuf();

	inputFile.close();

	return buffer.str();
}
