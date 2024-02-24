#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "commons/ShuntingYard.h"
#include "../Utils.h"

TEST_CASE("qps/QueryProcessingSubsystem: AssignPatternReader Updated Integration Test") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto assignPatternWriter = pkbManager->getPKBWriterManager()->getAssignPatternWriter();
    auto pkbReaderManager = pkbManager->getPKBReaderManager();
    auto variableWriter = pkbManager->getPKBWriterManager()->getVariableWriter();
    auto assignWriter = pkbManager->getPKBWriterManager()->getAssignWriter();

    // Prepare the environment: Clear the store before populating it to ensure a clean state.
    assignPatternWriter->clear();

    // Populating assignment patterns for retrieval tests, based on the assumption provided.
    int stmtNum1 = 1;
    std::string lhs1 = "x", rhs1 = "v + x * y + z * t";
    variableWriter->insertVariable(lhs1);
    assignPatternWriter->addAssignPattern(stmtNum1, lhs1, ShuntingYard::convertToPostfix(rhs1));
    assignWriter->insertAssign(stmtNum1);

    SECTION("Wildcard RHS Pattern Match") {
        std::string queryWildcard = "assign a; Select a pattern a(_, _)";
        auto resultWildcard = Utils::getResultsFromQuery(queryWildcard, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsWildcard = {"1"};
        REQUIRE(resultWildcard == expectedResultsWildcard);
    }

    SECTION("Partial Matching with Variable in RHS Pattern") {
        // Tests based on rules: pattern a(_, _"x"_) should be valid.
        std::string queryPartialMatchVariable = R"(assign a; Select a pattern a(_, _"x"_))";
        auto resultPartialMatchVariable = Utils::getResultsFromQuery(queryPartialMatchVariable, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsPartialMatchVariable = {"1"};
        REQUIRE(resultPartialMatchVariable == expectedResultsPartialMatchVariable);
    }

    SECTION("Partial Matching with Constant in RHS Pattern") {
        // Tests based on rules: pattern a(_, _"1"_) should be valid.
        std::string queryPartialMatchConstant = R"(assign a; Select a pattern a(_, _"1"_))";
        auto resultPartialMatchConstant = Utils::getResultsFromQuery(queryPartialMatchConstant, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsPartialMatchConstant = {"1"};
        REQUIRE(resultPartialMatchConstant == expectedResultsPartialMatchConstant);
    }
    
}
