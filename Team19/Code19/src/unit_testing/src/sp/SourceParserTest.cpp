#include "sp/SPTokenizer/Tokenizer.h"
#include "sp/SourceProcessor.h"
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

TEST_CASE("Test header", "[SourceProcessor]") {
    std::cout << "AST-DESIGN-EXTRACTOR-TEST STARTS\n\n\n" << std::endl;  
    const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";
    const std::string testFileContent = "x = 1;";

    std::string actualContent;
    REQUIRE(std::filesystem::exists(testFileName));

    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    SourceProcessor sp(testFileName, pkbManager);

    REQUIRE_NOTHROW(sp.parseSIMPLE());
    REQUIRE_NOTHROW(sp.extractAndPopulate());

    std::shared_ptr<PKBReaderManager> pkbReaderManager = sp.pkbManager->getPKBReaderManager();
    auto variableReader = pkbReaderManager->getVariableReader();
    auto values1 = variableReader->getAllVariables();
    std::cout << "All Extracted variables: ";
    for (auto& var : values1) {
		std::cout << var << ", ";
	}
    std::cout << std::endl;

    std::cout << "AST-DESIGN-EXTRACTOR-TEST ENDS\n\n\n" << std::endl;
}