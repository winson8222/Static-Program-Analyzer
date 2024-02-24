#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "../Utils.h" // Assuming Utils.h is available for utility functions

TEST_CASE("qps/QueryProcessingSubsystem: ConstantReader Integration Test") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto constantWriter = pkbManager->getPKBWriterManager()->getConstantWriter();

    // Preparing the environment: Clearing the store before populating it to ensure a clean state.
    constantWriter->clear();

    // Populating some constants for retrieval tests.
    constantWriter->insertConstant(1);
    constantWriter->insertConstant(2);
    constantWriter->insertConstant(3);

    auto pkbReaderManager = pkbManager->getPKBReaderManager();

    SECTION("Verify retrieval of all constants via QPS") {
        std::string query = "constant c; Select c";
        auto results = Utils::getResultsFromQuery(query, pkbReaderManager);
        std::unordered_set<std::string> expectedResults = {"1", "2", "3"};
        REQUIRE(results == expectedResults);
    }


    SECTION("Test for constants in expressions via QPS") {
        std::string queryForConstInExpressions = R"(assign a; pattern a(_, _"1 + 2"_))";
        auto resultsForConstInExpressions = Utils::getResultsFromQuery(queryForConstInExpressions, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsForConstInExpressions;
        REQUIRE(resultsForConstInExpressions == expectedResultsForConstInExpressions);
    }
}
