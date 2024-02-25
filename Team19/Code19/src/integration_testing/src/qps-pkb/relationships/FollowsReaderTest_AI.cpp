#include "catch.hpp"
#include <memory>
#include <string>
#include "pkb/PKBManager.h"
#include "../Utils.h"

TEST_CASE("qps/QueryProcessingSubsystem: FollowsReader Integration Test") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto followsWriter = pkbManager->getPKBWriterManager()->getFollowsWriter();
    auto statementWriter = pkbManager->getPKBWriterManager()->getStatementWriter();

    // Setup PKB with Follows relationships
    followsWriter->clear();
    statementWriter->clear();
    followsWriter->addFollows(1, 2);
    followsWriter->addFollows(2, 3);
    followsWriter->addFollows(3, 4);
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);

    auto pkbReaderManager = pkbManager->getPKBReaderManager();

    SECTION("Statements directly following a given statement") {
        std::string queryDirectFollows = "stmt s; Select s such that Follows(1, s)";
        auto resultsDirectFollows = Utils::getResultsFromQuery(queryDirectFollows, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsDirectFollows = {"2"};
        REQUIRE(resultsDirectFollows == expectedResultsDirectFollows);
    }

    SECTION("Statements that directly follow any statement") {
        std::string queryDirectlyFollowsAny = "stmt s; Select s such that Follows(s, _)";
        auto resultsDirectlyFollowsAny = Utils::getResultsFromQuery(queryDirectlyFollowsAny, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsDirectlyFollowsAny = {"1", "2", "3"};
        REQUIRE(resultsDirectlyFollowsAny == expectedResultsDirectlyFollowsAny);
    }

    SECTION("Statements directly followed by any statement") {
        std::string queryDirectlyFollowedByAny = "stmt s; Select s such that Follows(_, s)";
        auto resultsDirectlyFollowedByAny = Utils::getResultsFromQuery(queryDirectlyFollowedByAny, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsDirectlyFollowedByAny = {"2", "3", "4"};
        REQUIRE(resultsDirectlyFollowedByAny == expectedResultsDirectlyFollowedByAny);
    }

    SECTION("Verify non-existent Follows relationship") {
        std::string queryNonExistentFollows = "stmt s; Select s such that Follows(999, s)";
        auto resultsNonExistentFollows = Utils::getResultsFromQuery(queryNonExistentFollows, pkbReaderManager);
        REQUIRE(resultsNonExistentFollows.empty());
    }

}
