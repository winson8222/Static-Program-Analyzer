#include "catch.hpp"
#include <memory>
#include <string>
#include "pkb/PKBManager.h"
#include "../Utils.h"

TEST_CASE("qps/QueryProcessingSubsystem: FollowsTReader Integration Test") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto followsTWriter = pkbManager->getPKBWriterManager()->getFollowsTWriter();
    auto statementWriter = pkbManager->getPKBWriterManager()->getStatementWriter();

    // Setup PKB with FollowsT relationships
    followsTWriter->clear();
    statementWriter->clear();
    followsTWriter->addFollowsT(1, 2);
    followsTWriter->addFollowsT(2, 3);
    followsTWriter->addFollowsT(3, 4);
    followsTWriter->addFollowsT(1, 3);
    followsTWriter->addFollowsT(1, 4);
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);

    auto pkbReaderManager = pkbManager->getPKBReaderManager();
    auto pkbCacheManager = pkbManager->getPKBCacheManager();

    SECTION("Statements directly followed by a given statement") {
        std::string query = "stmt s; Select s such that Follows*(1, s)";
        auto results = Utils::getResultsFromQuery(query, pkbReaderManager, pkbCacheManager);
        std::unordered_set<std::string> expectedResults = {"2", "3", "4"};
        REQUIRE(results == expectedResults);
    }

    SECTION("Statements that follow any statement") {
        std::string query = "stmt s; Select s such that Follows*(s, _)";
        auto results = Utils::getResultsFromQuery(query, pkbReaderManager, pkbCacheManager);
        std::unordered_set<std::string> expectedResults = {"1", "2", "3"};
        REQUIRE(results == expectedResults);
    }

    SECTION("Statements followed by any statement") {
        std::string query = "stmt s; Select s such that Follows*(_, s)";
        auto results = Utils::getResultsFromQuery(query, pkbReaderManager, pkbCacheManager);
        std::unordered_set<std::string> expectedResults = {"2", "3", "4"};
        REQUIRE(results == expectedResults);
    }

    SECTION("Verify individual FollowsT relationships via QPS") {
        // Testing FollowsT(s, 1) should yield no results
        std::string query1 = "stmt s; Select s such that Follows*(s, 1)";
        auto results1 = Utils::getResultsFromQuery(query1, pkbReaderManager, pkbCacheManager);
        std::unordered_set<std::string> expectedResults1 = {};
        REQUIRE(results1 == expectedResults1);
    }

}
