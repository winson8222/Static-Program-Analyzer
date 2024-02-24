#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: IfReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto ifWriter = pkbManager->getPKBWriterManager()->getIfWriter();

    // Preparing the environment: Clearing the store before populating it to ensure a clean state.
    ifWriter->clear();

    // Populating some "if" statements for retrieval tests.
    int stmtNum1 = 2;
    int stmtNum2 = 6;
    ifWriter->insertIf(stmtNum1);
    ifWriter->insertIf(stmtNum2);

    auto ifReader = pkbManager->getPKBReaderManager()->getIfReader();

    SECTION("Verify retrieval of all 'if' statement numbers") {
        std::unordered_set<int> expectedIfs = {stmtNum1, stmtNum2};
        auto retrievedIfs = ifReader->getAllIfs();
        REQUIRE(retrievedIfs == expectedIfs);
    }

    SECTION("Check specific 'if' statements exist") {
        REQUIRE(ifReader->contains(stmtNum1) == true);
        REQUIRE(ifReader->contains(stmtNum2) == true);
        REQUIRE(ifReader->contains(999) == false); // Test for an 'if' statement number that doesn't exist.
    }

    SECTION("Check if IfStore is empty") {
        REQUIRE(ifReader->isEmpty() == false);
    }

    SECTION("Test retrieval after clearing 'if' statements") {
        ifWriter->clear(); // Clear all 'if' statements.
        REQUIRE(ifReader->isEmpty() == true);
        REQUIRE(ifReader->contains(stmtNum1) == false);
        REQUIRE(ifReader->contains(stmtNum2) == false);
    }

        // Testing Nested If Statements
    SECTION("Test for nested 'if' statements") {
        int outerIf = 10;
        int innerIf = 11; // Assuming innerIf is nested within outerIf
        ifWriter->insertIf(outerIf);
        ifWriter->insertIf(innerIf);

        REQUIRE(ifReader->contains(outerIf) == true);
        REQUIRE(ifReader->contains(innerIf) == true);
    }

        // Testing If Statements with Various Control Constructs
    SECTION("Test for 'if' statements with various control constructs") {
        int ifWithWhile = 12; // If statement that contains a while loop
        ifWriter->insertIf(ifWithWhile);

        REQUIRE(ifReader->contains(ifWithWhile) == true);
    }

}
