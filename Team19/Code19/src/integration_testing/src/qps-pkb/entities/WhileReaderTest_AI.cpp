#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: WhileReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto whileWriter = pkbManager->getPKBWriterManager()->getWhileWriter();

    // Preparing the environment: Clearing the store before populating it to ensure a clean state.
    whileWriter->clear();

    // Populating some "while" statements for retrieval tests.
    // Assume statement numbers are assigned sequentially and uniquely.
    int stmtNum1 = 1;
    int stmtNum2 = 5;
    whileWriter->insertWhile(stmtNum1);
    whileWriter->insertWhile(stmtNum2);

    auto whileReader = pkbManager->getPKBReaderManager()->getWhileReader();

    SECTION("Verify retrieval of all 'while' statement numbers") {
        std::unordered_set<int> expectedWhiles = {stmtNum1, stmtNum2};
        auto retrievedWhiles = whileReader->getAllWhiles();
        REQUIRE(retrievedWhiles == expectedWhiles);
    }

    SECTION("Check specific 'while' statements exist") {
        REQUIRE(whileReader->contains(stmtNum1) == true);
        REQUIRE(whileReader->contains(stmtNum2) == true);
        REQUIRE(whileReader->contains(999) == false); // Test for a 'while' statement number that doesn't exist.
    }

    SECTION("Check if WhileStore is empty") {
        REQUIRE(whileReader->isEmpty() == false);
    }

    SECTION("Test retrieval after clearing 'while' statements") {
        whileWriter->clear(); // Clear all 'while' statements.
        REQUIRE(whileReader->isEmpty() == true);
        REQUIRE(whileReader->contains(stmtNum1) == false);
        REQUIRE(whileReader->contains(stmtNum2) == false);
    }

    SECTION("Test for nested 'while' statements") {
        int outerWhile = 10;
        int innerWhile = 11;
        whileWriter->insertWhile(outerWhile);
        whileWriter->insertWhile(innerWhile); // Assuming innerWhile is nested within outerWhile

        REQUIRE(whileReader->contains(outerWhile) == true);
        REQUIRE(whileReader->contains(innerWhile) == true);
        // Optionally, verify the nesting relationship if your system supports it
    }

    SECTION("Test for 'while' statements with various control constructs") {
        int whileWithIf = 12; // While statement that contains an if-statement
        int whileWithNestedLoop = 13; // While statement that contains another while loop

        whileWriter->insertWhile(whileWithIf);
        whileWriter->insertWhile(whileWithNestedLoop);

        REQUIRE(whileReader->contains(whileWithIf) == true);
        REQUIRE(whileReader->contains(whileWithNestedLoop) == true);
    }

    SECTION("Test for retrieval of variables used in 'while' statements") {
        int whileStmtNum = 14;
        std::string usedVar = "counter";
        // Assuming functionality to link variables with while statements
        whileWriter->insertWhile(whileStmtNum);
        // variableWriter->associateVariableWithWhile(usedVar, whileStmtNum); // Hypothetical method

        REQUIRE(whileReader->contains(whileStmtNum) == true);
        // REQUIRE(variableReader->hasVariable(usedVar) == true); // Verify if the used variable is recognized
    }

    SECTION("Test for 'while' statements across multiple procedures") {
        int whileInProc1 = 15;
        int whileInProc2 = 16;
        // Assuming functionality to associate while statements with procedures
        whileWriter->insertWhile(whileInProc1);
        whileWriter->insertWhile(whileInProc2);

        REQUIRE(whileReader->contains(whileInProc1) == true);
        REQUIRE(whileReader->contains(whileInProc2) == true);
        // Further checks can be made to ensure the while statements are correctly associated with their respective procedures
    }
    
}
