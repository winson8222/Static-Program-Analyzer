#include "sp/Tokenizer.h"
#include "sp/SourceProcessor.h"
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

TEST_CASE("Test parser of SP on multiple procedures", "[SourceProcessor]") {
    std::cout << "\n\nSP-PKB-WORKFLOW-TEST STARTS\n\n\n" << std::endl;
    const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";

    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    SourceProcessor sp(testFileName, pkbManager);

    REQUIRE_NOTHROW(sp.parseSIMPLE());
    REQUIRE_NOTHROW(sp.extractAndPopulate());

    std::shared_ptr<PKBReader> pkbReader = pkbManager->getPKBReader();

    auto values1 = pkbReader->getAllVariables();
    std::cout << "All Extracted variables: ";
    for (auto& var : values1) {
        std::cout << var << ", ";
    }
    std::cout << std::endl;

    auto values2 = pkbReader->getAllProcedures();
    std::cout << "All Extracted procedures: ";
    for (auto& proc : values2) {
		std::cout << proc << ", ";
	}
    std::cout << std::endl;

    auto values3 = pkbReader->getAllStmts();
    std::cout << "All Extracted statements: ";
    for (auto& stmt : values3) {
         std::cout << stmt << ", ";
    }
    std::cout << std::endl;

    std::cout << "SP-PKB-WORKFLOW-TEST ENDS\n\n\n" << std::endl;
}


TEST_CASE("Test parser of SP on one procedures and multiple statements", "[SourceProcessor]") {
    std::cout << "\n\nSP-PKB-WORKFLOW-TEST STARTS\n\n\n" << std::endl;
    const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure1.txt";

    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    SourceProcessor sp(testFileName, pkbManager);

    REQUIRE_NOTHROW(sp.parseSIMPLE());
    REQUIRE_NOTHROW(sp.extractAndPopulate());

    std::shared_ptr<PKBReader> pkbReader = pkbManager->getPKBReader();

    auto values1 = pkbReader->getAllVariables();
    std::cout << "All Extracted variables: ";
    for (auto& var : values1) {
        std::cout << var << ", ";
    }
    std::cout << std::endl;

    auto values2 = pkbReader->getAllProcedures();
    std::cout << "All Extracted procedures: ";
    for (auto& proc : values2) {
        std::cout << proc << ", ";
    }
    std::cout << std::endl;

    auto values3 = pkbReader->getAllStmts();
    std::cout << "All Extracted statements: ";
    for (auto& stmt : values3) {
        std::cout << stmt << ", ";
    }
    std::cout << std::endl;

    std::cout << "SP-PKB-WORKFLOW-TEST ENDS\n\n\n" << std::endl;
}