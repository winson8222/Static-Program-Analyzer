#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "commons/ShuntingYard.h"
#include "../Utils.h"

TEST_CASE("qps/QueryProcessingSubsystem: AssignPatternReader Integration Test") {
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
        std::string queryPartialMatchVariable = R"(assign a; Select a pattern a(_, _"x"_))";
        auto resultPartialMatchVariable = Utils::getResultsFromQuery(queryPartialMatchVariable, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsPartialMatchVariable = {"1"};
        REQUIRE(resultPartialMatchVariable == expectedResultsPartialMatchVariable);
    }

    SECTION("Partial Matching with Constant in RHS Pattern") {
        std::string queryPartialMatchConstant = R"(assign a; Select a pattern a(_, _"1"_))";
        auto resultPartialMatchConstant = Utils::getResultsFromQuery(queryPartialMatchConstant, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsPartialMatchConstant = {"1"};
        REQUIRE(resultPartialMatchConstant == expectedResultsPartialMatchConstant);
    }

        // Negative Test Cases
    SECTION("Invalid Partial Match RHS with Operators") {
        // This query attempts a partial match with an expression containing operators, which should not yield results.
        std::string queryInvalidPartial = R"(assign a; Select a pattern a(_, _"x + 1"_))";
        auto resultsInvalidPartial = Utils::getResultsFromQuery(queryInvalidPartial, pkbReaderManager);
        REQUIRE(resultsInvalidPartial.empty());
    }


    SECTION("Non-Existent Variable in RHS Pattern") {
        // This query attempts to match a pattern with a non-existent variable in the RHS, which should yield no results.
        std::string queryNonExistentVariable = R"(assign a; Select a pattern a(_, _"nonExistentVar"_))";
        auto resultsNonExistentVariable = Utils::getResultsFromQuery(queryNonExistentVariable, pkbReaderManager);
        REQUIRE(resultsNonExistentVariable.empty());
    }
}
