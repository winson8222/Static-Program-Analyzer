#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SPTokenizer/LexicalToken.h"
#include "sp/SPTokenizer/FileProcessor.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>

TEST_CASE("Tokenizer throws error for invalid syntax", "[tokenize]") {
    REQUIRE_THROWS_WITH(SPTokenizer::tokenize("0123a = y;"), "Error: Invalid SIMPLE syntax.");
}

TEST_CASE("Procedure test", "[tokenize]") {
    std::vector<LexicalToken> output = SPTokenizer::tokenize("procedure procedure { procedure = procedure + 1; }");
    for (auto token : output) {
		std::cout << LexicalTokenTypeMapper::tokenToStringMap.find(token.getTokenType())->second << std::endl;
	}
}
