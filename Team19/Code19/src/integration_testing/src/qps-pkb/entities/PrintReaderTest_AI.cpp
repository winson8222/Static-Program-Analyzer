#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "../Utils.h" // Assuming Utils.h is available for utility functions

TEST_CASE("qps/QueryProcessingSubsystem: PrintReader Integration Test") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto printWriter = pkbManager->getPKBWriterManager()->getPrintWriter();

    // Clearing previous data for a clean state
    printWriter->clear();

    // Populating "print" statements for retrieval tests
    printWriter->insertPrint(3);
    printWriter->insertPrint(7);
    // Assume you also need to insert these as statements in relevant stores

    auto pkbReaderManager = pkbManager->getPKBReaderManager();

    SECTION("Verify retrieval of all 'print' statement numbers via QPS") {
        std::string query = "print p; Select p";
        auto results = Utils::getResultsFromQuery(query, pkbReaderManager);
        std::unordered_set<std::string> expectedResults = {"3", "7"};
        REQUIRE(results == expectedResults);
    }


}
