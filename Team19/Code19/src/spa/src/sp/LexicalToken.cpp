// Include the header file for the LexicalToken class.
#include "LexicalToken.h"
#include <regex>

namespace LexicalTokens {
	bool Letter::verifyToken(std::string str) const {
		return std::regex_match(str, std::regex(R"([A-Za-z])"));
	}

	bool Digit::verifyToken(std::string str) const {
		return std::regex_match(str, std::regex(R"(\d)"));
	}

	bool Name::verifyToken(std::string str) const {
		return std::regex_match(str, std::regex(R"([A-Za-z][A-Za-z0-9]*)"));
	}

	bool Integer::verifyToken(std::string str) const {
		return std::regex_match(str, std::regex(R"(\d+)"));
	}
}
