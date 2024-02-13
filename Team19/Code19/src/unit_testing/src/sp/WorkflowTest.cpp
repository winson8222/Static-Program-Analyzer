#include "sp/SPTokenizer/Tokenizer.h"
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

    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

    auto variableReader = pkbReaderManager->getVariableReader();
    auto values1 = variableReader->getAllVariables();
    std::unordered_set<std::string> expectedValues1 = {"x", "y", "z"};
    REQUIRE(values1 == expectedValues1);

    auto procedureReader = pkbReaderManager->getProcedureReader();
    auto values2 = procedureReader->getAllProcedures();

    auto statementReader = pkbReaderManager->getStatementReader();
    auto values3 = statementReader->getAllStatements();
    std::unordered_set<int> expectedValues3 = {2, 6, 10};
    REQUIRE(values3 == expectedValues3);

    std::cout << "SP-PKB-WORKFLOW-TEST ENDS\n\n\n" << std::endl;
}


TEST_CASE("Test parser of SP on one procedures and multiple statements", "[SourceProcessor]") {
    std::cout << "\n\nSP-PKB-WORKFLOW-TEST STARTS\n\n\n" << std::endl;
    const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure1.txt";

    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    SourceProcessor sp(testFileName, pkbManager);

    REQUIRE_NOTHROW(sp.parseSIMPLE());
    REQUIRE_NOTHROW(sp.extractAndPopulate());

    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    auto variableReader = pkbReaderManager->getVariableReader();
    auto values1 = variableReader->getAllVariables();
    std::unordered_set<std::string> expectedValues1 = { "x", "y", "z" };
    REQUIRE(values1 == expectedValues1);

    auto procedureReader = pkbReaderManager->getProcedureReader();
    auto values2 = procedureReader->getAllProcedures();

    auto statementReader = pkbReaderManager->getStatementReader();
    auto values3 = statementReader->getAllStatements();
    std::unordered_set<int> expectedValues3 = { 2, 3, 4 };
    REQUIRE(values3 == expectedValues3);

    std::cout << "SP-PKB-WORKFLOW-TEST ENDS\n\n\n" << std::endl;
}