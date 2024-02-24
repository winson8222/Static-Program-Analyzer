#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: CallReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto callWriter = pkbManager->getPKBWriterManager()->getCallWriter();

    // Preparing the environment: Clearing the store before populating it to ensure a clean state.
    callWriter->clear();

    // Populating some "call" statements for retrieval tests.
    int stmtNum1 = 3;
    int stmtNum2 = 7;
    callWriter->insertCall(stmtNum1);
    callWriter->insertCall(stmtNum2);

    auto callReader = pkbManager->getPKBReaderManager()->getCallReader();

    SECTION("Verify retrieval of all 'call' statement numbers") {
        std::unordered_set<int> expectedCalls = {stmtNum1, stmtNum2};
        auto retrievedCalls = callReader->getAllCalls();
        REQUIRE(retrievedCalls == expectedCalls);
    }

    SECTION("Check specific 'call' statements exist") {
        REQUIRE(callReader->contains(stmtNum1) == true);
        REQUIRE(callReader->contains(stmtNum2) == true);
        REQUIRE(callReader->contains(999) == false); // Test for a 'call' statement number that doesn't exist.
    }

    SECTION("Check if CallStore is empty") {
        REQUIRE(callReader->isEmpty() == false);
    }

    SECTION("Test retrieval after clearing 'call' statements") {
        callWriter->clear(); // Clear all 'call' statements.
        REQUIRE(callReader->isEmpty() == true);
        REQUIRE(callReader->contains(stmtNum1) == false);
        REQUIRE(callReader->contains(stmtNum2) == false);
    }

        // Testing Call Statements in Different Procedures
    SECTION("Test for 'call' statements in different procedures") {
        int callInProc1 = 8; // Assuming callInProc1 is in Procedure 1
        int callInProc2 = 9; // Assuming callInProc2 is in Procedure 2
        callWriter->insertCall(callInProc1);
        callWriter->insertCall(callInProc2);

        REQUIRE(callReader->contains(callInProc1) == true);
        REQUIRE(callReader->contains(callInProc2) == true);
    }

}
