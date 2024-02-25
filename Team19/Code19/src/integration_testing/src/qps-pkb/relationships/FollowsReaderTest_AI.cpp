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

//    SECTION("Verify Follows relationships via QPS") {
//        std::string query = "stmt s1, s2; Select <s1, s2> such that Follows(s1, s2)";
//        auto results = Utils::getResultsFromQuery(query, pkbReaderManager);
//        std::unordered_set<std::string> expectedResults = {"<1, 2>", "<3, 4>"};
//        REQUIRE(results == expectedResults);
//    }

    SECTION("Verify individual Follows relationships via QPS") {
        // Testing Follows(s, 1) should yield no results
        std::string query1 = "stmt s; Select s such that Follows(s, 1)";
        auto results1 = Utils::getResultsFromQuery(query1, pkbReaderManager);
        std::unordered_set<std::string> expectedResults1 = {};
        REQUIRE(results1 == expectedResults1);

        // Testing Follows(2, s) should yield {3}
        std::string query2 = "stmt s; Select s such that Follows(2, s)";
        auto results2 = Utils::getResultsFromQuery(query2, pkbReaderManager);
        std::unordered_set<std::string> expectedResults2 = {"3"};
        REQUIRE(results2 == expectedResults2);
    }

}