#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: PrintReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto printWriter = pkbManager->getPKBWriterManager()->getPrintWriter();

    // Preparing the environment: Clearing the store before populating it to ensure a clean state.
    printWriter->clear();

    // Populating some "print" statements for retrieval tests.
    int stmtNum1 = 3;
    int stmtNum2 = 7;
    printWriter->insertPrint(stmtNum1);
    printWriter->insertPrint(stmtNum2);

    auto printReader = pkbManager->getPKBReaderManager()->getPrintReader();

    SECTION("Verify retrieval of all 'print' statement numbers") {
        std::unordered_set<int> expectedPrints = {stmtNum1, stmtNum2};
        auto retrievedPrints = printReader->getAllPrints();
        REQUIRE(retrievedPrints == expectedPrints);
    }

    SECTION("Check specific 'print' statements exist") {
        REQUIRE(printReader->contains(stmtNum1) == true);
        REQUIRE(printReader->contains(stmtNum2) == true);
        REQUIRE(printReader->contains(999) == false); // Test for a 'print' statement number that doesn't exist.
    }

    SECTION("Check if PrintStore is empty") {
        REQUIRE(printReader->isEmpty() == false);
    }

    SECTION("Test retrieval after clearing 'print' statements") {
        printWriter->clear(); // Clear all 'print' statements.
        REQUIRE(printReader->isEmpty() == true);
        REQUIRE(printReader->contains(stmtNum1) == false);
        REQUIRE(printReader->contains(stmtNum2) == false);
    }

}
