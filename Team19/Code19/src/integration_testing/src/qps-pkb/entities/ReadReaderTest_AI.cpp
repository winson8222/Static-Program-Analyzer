#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: ReadReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto readWriter = pkbManager->getPKBWriterManager()->getReadWriter();

    // Preparing the environment: Clearing the store before populating it to ensure a clean state.
    readWriter->clear();

    // Populating some "read" statements for retrieval tests.
    int stmtNum1 = 4;
    int stmtNum2 = 8;
    readWriter->insertRead(stmtNum1);
    readWriter->insertRead(stmtNum2);

    auto readReader = pkbManager->getPKBReaderManager()->getReadReader();

    SECTION("Verify retrieval of all 'read' statement numbers") {
        std::unordered_set<int> expectedReads = {stmtNum1, stmtNum2};
        auto retrievedReads = readReader->getAllReads();
        REQUIRE(retrievedReads == expectedReads);
    }

    SECTION("Check specific 'read' statements exist") {
        REQUIRE(readReader->contains(stmtNum1) == true);
        REQUIRE(readReader->contains(stmtNum2) == true);
        REQUIRE(readReader->contains(999) == false); // Test for a 'read' statement number that doesn't exist.
    }

    SECTION("Check if ReadStore is empty") {
        REQUIRE(readReader->isEmpty() == false);
    }

    SECTION("Test retrieval after clearing 'read' statements") {
        readWriter->clear(); // Clear all 'read' statements.
        REQUIRE(readReader->isEmpty() == true);
        REQUIRE(readReader->contains(stmtNum1) == false);
        REQUIRE(readReader->contains(stmtNum2) == false);
    }

}
