#include "catch.hpp"
#include <memory>
#include <string>
#include "pkb/PKBManager.h"
#include "../Utils.h"

TEST_CASE("qps/QueryProcessingSubsystem: ParentReader Integration Test") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto parentWriter = pkbManager->getPKBWriterManager()->getParentWriter();
    auto statementWriter = pkbManager->getPKBWriterManager()->getStatementWriter();

    // Setup PKB with Parent relationships
    parentWriter->clear();
    statementWriter->clear();
    // Setting up a basic hierarchy for testing
    parentWriter->addParent(1, 2); // 1 is the parent of 2
    parentWriter->addParent(2, 3); // 2 is the parent of 3
    // Inserting statements for completeness
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);

    auto pkbReaderManager = pkbManager->getPKBReaderManager();

    SECTION("Verify statements with no parent via QPS") {
        // Query to find statements that are not a parent to any statement
        std::string queryNoParent = "stmt s; Select s such that Parent(s, _)";
        auto resultsNoParent = Utils::getResultsFromQuery(queryNoParent, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsNoParent = {"1", "2"};
        REQUIRE(resultsNoParent == expectedResultsNoParent);
    }

    SECTION("Verify child statements of a specific parent via QPS") {
        // Query to find child statements of statement 1
        std::string queryChildOf1 = "stmt s; Select s such that Parent(1, s)";
        auto resultsChildOf1 = Utils::getResultsFromQuery(queryChildOf1, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsChildOf1 = {"2"};
        REQUIRE(resultsChildOf1 == expectedResultsChildOf1);

        // Query to find child statements of statement 2
        std::string queryChildOf2 = "stmt s; Select s such that Parent(2, s)";
        auto resultsChildOf2 = Utils::getResultsFromQuery(queryChildOf2, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsChildOf2 = {"3"};
        REQUIRE(resultsChildOf2 == expectedResultsChildOf2);
    }

    SECTION("Verify non-existent Parent relationship via QPS") {
        // Query for a non-existent Parent relationship
        std::string queryNonExistentParent = "stmt s; Select s such that Parent(999, s)";
        auto resultsNonExistentParent = Utils::getResultsFromQuery(queryNonExistentParent, pkbReaderManager);
        REQUIRE(resultsNonExistentParent.empty()); // Expect no results for a non-existent parent
    }
}
