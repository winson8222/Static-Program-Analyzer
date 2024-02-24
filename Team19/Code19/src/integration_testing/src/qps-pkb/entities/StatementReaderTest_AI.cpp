#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: StatementReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto statementWriter = pkbManager->getPKBWriterManager()->getStatementWriter();

    // Clearing the store before populating it to ensure a clean state.
    statementWriter->clear();

    // Populating some statements for retrieval tests.
    int stmtNum1 = 1;
    int stmtNum2 = 2;
    int stmtNum3 = 3;
    statementWriter->insertStatement(stmtNum1);
    statementWriter->insertStatement(stmtNum2);
    statementWriter->insertStatement(stmtNum3);

    auto statementReader = pkbManager->getPKBReaderManager()->getStatementReader();

    SECTION("Verify retrieval of all statements") {
        std::unordered_set<int> expectedStatements = {stmtNum1, stmtNum2, stmtNum3};
        auto retrievedStatements = statementReader->getAllStatements();
        REQUIRE(retrievedStatements == expectedStatements);
    }

    SECTION("Check specific statements exist") {
        REQUIRE(statementReader->contains(stmtNum1) == true);
        REQUIRE(statementReader->contains(stmtNum2) == true);
        REQUIRE(statementReader->contains(stmtNum3) == true);
        REQUIRE(statementReader->contains(999) == false); // Test for a statement number that doesn't exist.
    }

    SECTION("Check if StatementStore is empty") {
        REQUIRE(statementReader->isEmpty() == false);
    }

    SECTION("Test retrieval after clearing statements") {
        statementWriter->clear(); // Clear all statements.
        REQUIRE(statementReader->isEmpty() == true);
        REQUIRE(statementReader->contains(stmtNum1) == false);
        REQUIRE(statementReader->contains(stmtNum2) == false);
        REQUIRE(statementReader->contains(stmtNum3) == false);
    }

}
