#include "catch.hpp"
#include <memory>
#include <string>
#include "pkb/PKBManager.h"
#include "../Utils.h"

TEST_CASE("qps/QueryProcessingSubsystem: ParentTReader Integration Test") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto parentTWriter = pkbManager->getPKBWriterManager()->getParentTWriter();
    auto statementWriter = pkbManager->getPKBWriterManager()->getStatementWriter();

    // Setup PKB with ParentT relationships
    parentTWriter->clear();
    statementWriter->clear();
    // Setting up a hierarchical structure for testing ParentT
    parentTWriter->addParentT(1, 2); // 1 is the parent of 2
    parentTWriter->addParentT(1, 3); // 1 is also an indirect parent of 3 through 2
    parentTWriter->addParentT(2, 3); // 2 is the direct parent of 3
    // Inserting statements for completeness
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);

    auto pkbReaderManager = pkbManager->getPKBReaderManager();
    auto pkbCacheManager = pkbManager->getPKBCacheManager();

    SECTION("Verify direct and indirect ParentT relationships via QPS") {
        // Query to find all statements that have a parent (direct or indirect)
        std::string queryAllChildren = "stmt s; Select s such that Parent*(1, s)";
        auto resultsAllChildren = Utils::getResultsFromQuery(queryAllChildren,pkbReaderManager, pkbCacheManager);
        std::unordered_set<std::string> expectedResultsAllChildren = {"2", "3"};
        REQUIRE(resultsAllChildren == expectedResultsAllChildren);
    }

    SECTION("Verify statements with no indirect parent via QPS") {
        // Query to find statements that do not have an indirect parent
        std::string queryNoIndirectParent = "stmt s; Select s such that Parent*(s, _)";
        auto resultsNoIndirectParent = Utils::getResultsFromQuery(queryNoIndirectParent,pkbReaderManager, pkbCacheManager);
        // Expect to find statements that are parents but not as a result of transitivity
        std::unordered_set<std::string> expectedResultsNoIndirectParent = {"1", "2"};
        REQUIRE(resultsNoIndirectParent == expectedResultsNoIndirectParent);
    }

    SECTION("Verify non-existent ParentT relationship via QPS") {
        // Query for a non-existent ParentT relationship
        std::string queryNonExistentParentT = "stmt s; Select s such that Parent*(999, s)";
        auto resultsNonExistentParentT = Utils::getResultsFromQuery(queryNonExistentParentT,pkbReaderManager, pkbCacheManager);
        REQUIRE(resultsNonExistentParentT.empty()); // Expect no results for a non-existent transitive parent
    }


}
