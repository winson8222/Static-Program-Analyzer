#include "sp/SPTokenizer/SPTokenizer.h"
#include "LexicalToken.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <stdexcept>

// ai-gen start (copilot, 2, e)
// prompt: GitHub Copilot

std::vector<std::string> SPTokenizer::splitLine(const std::string& content) {
	std::vector<std::string> result;
	std::istringstream stream(content); // Create a stringstream from the content
	std::string line;
	while (std::getline(stream, line)) {
		result.push_back(line);
	}
	return result;
}

std::vector<LexicalToken> SPTokenizer::tokenize(const std::string& content) {
	std::vector<LexicalToken> results;
	std::vector<std::string> lines = SPTokenizer::splitLine(content);
	int numberOfLines = static_cast<int>(lines.size());

	bool isPreviousTokenKeyword = false;

	for (int lineNumber = 1; lineNumber <= numberOfLines; lineNumber++) {
		std::string line = lines[lineNumber - 1];
		std::string originalLine = line.substr();

		while (!line.empty()) {
			bool matchedSomething = false;
			for (auto const& rule : LexicalTokenTypeMapper::tokenToRegexPairs) {
				std::smatch match;
				if (!std::regex_search(line, match, std::regex(rule.second))) {
					continue;
				}
				LexicalTokenType type = rule.first;

				LexicalToken t(type, lineNumber, (int)(originalLine.size() - line.size()), match.str());
				assertValidToken(type, match.str());

				if (rule.first != LexicalTokenType::WHITESPACE) {
					results.push_back(t);
				}
				matchedSomething = true;
				line = line.substr(match.str().size());
				break;
			}
			if (!matchedSomething) {
				throw std::runtime_error("Error: Invalid SIMPLE syntax.");
			}
		}

		if (lineNumber != lines.size()) {
			LexicalToken newLine(LexicalTokenType::WHITESPACE, lineNumber, -1, "new line");
			results.push_back(newLine);
		}
	}
	return results;
}

void SPTokenizer::assertValidToken(LexicalTokenType type, const std::string& name) {
	if (type != LexicalTokenType::NAME) {
		return;
	}
	std::string pattern = "([a-zA-Z][a-zA-Z0-9]*)"; // Pattern to match an alphanumeric string with the first character being a letter
	std::regex regexPattern(pattern);
	if (!std::regex_match(name, regexPattern)) {
		throw std::runtime_error("ERROR: Name not valid " + name);
	}
}

// ai-gen end
