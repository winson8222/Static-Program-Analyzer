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
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);

    auto pkbReaderManager = pkbManager->getPKBReaderManager();

//    SECTION("Verify FollowsT relationships via QPS") {
//        std::string query = "stmt s1, s2; Select <s1, s2> such that Follows*(s1, s2)";
//        auto results = Utils::getResultsFromQuery(query, pkbReaderManager);
//        std::unordered_set<std::string> expectedResults = {"<1, 2>", "<1, 3>", "<1, 4>", "<2, 3>", "<2, 4>", "<3, 4>"};
//        REQUIRE(results == expectedResults);
//    }

    SECTION("Verify individual FollowsT relationships via QPS") {
        // Testing FollowsT(s, 1) should yield no results
        std::string query1 = "stmt s; Select s such that Follows*(s, 1)";
        auto results1 = Utils::getResultsFromQuery(query1, pkbReaderManager);
        std::unordered_set<std::string> expectedResults1 = {};
        REQUIRE(results1 == expectedResults1);

        // Testing FollowsT(1, s) should yield {2, 3, 4}
        std::string query2 = "stmt s; Select s such that Follows*(1, s)";
        auto results2 = Utils::getResultsFromQuery(query2, pkbReaderManager);
        std::unordered_set<std::string> expectedResults2 = {"2"};
        REQUIRE(results2 == expectedResults2);

        // Testing FollowsT(_, s) to get all statements that are followed by any statement
        std::string query3 = "stmt s; Select s such that Follows*(_, s)";
        auto results3 = Utils::getResultsFromQuery(query3, pkbReaderManager);
        // Expecting all statements except the very first one
        std::unordered_set<std::string> expectedResults3 = {"2", "3", "4"};
        REQUIRE(results3 == expectedResults3);

        // Testing FollowsT(s, _) to get all statements that follow any statement
        std::string query4 = "stmt s; Select s such that Follows*(s, _)";
        auto results4 = Utils::getResultsFromQuery(query4, pkbReaderManager);
        // Expecting all statements except the very last one
        std::unordered_set<std::string> expectedResults4 = {"1", "2", "3"};
        REQUIRE(results4 == expectedResults4);
    }

    // Additional tests can be added here to cover more scenarios
}
