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
    std::vector<LexicalToken> output = SPTokenizer::tokenize("procedure procedure { procedure = 2 }");
    REQUIRE(output[0].getTokenType() == LexicalTokenType::KEYWORD_PROCEDURE);
    REQUIRE(output[1].getTokenType() == LexicalTokenType::NAME);

    std::cout << "procedure procedure { procedure = 2 }" << std::endl;
    for (auto val : output) {
        std::cout << LexicalTokenTypeMapper::tokenToStringMap.find(val.getTokenType())->second << std::endl;
	}

}
