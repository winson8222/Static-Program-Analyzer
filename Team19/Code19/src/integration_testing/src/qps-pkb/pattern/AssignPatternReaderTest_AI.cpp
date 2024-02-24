#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: AssignPatternReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto assignPatternWriter = pkbManager->getPKBWriterManager()->getAssignPatternWriter();

    // Prepare the environment: Clear the store before populating it to ensure a clean state.
    assignPatternWriter->clear();

    // Populating assignment patterns for retrieval tests.
    int stmtNum1 = 1, stmtNum2 = 2;
    std::string lhs1 = "x", rhs1 = "y + 1";
    std::string lhs2 = "z", rhs2 = "x * 2";
    assignPatternWriter->addAssignPattern(stmtNum1, lhs1, rhs1);
    assignPatternWriter->addAssignPattern(stmtNum2, lhs2, rhs2);

    auto assignPatternReader = pkbManager->getPKBReaderManager()->getAssignPatternReader();

    SECTION("Verify retrieval of all assignment patterns") {
        auto allPatterns = assignPatternReader->getAllPatterns();
        REQUIRE(allPatterns.size() == 2);
        REQUIRE(allPatterns[stmtNum1] == std::make_pair(lhs1, rhs1));
        REQUIRE(allPatterns[stmtNum2] == std::make_pair(lhs2, rhs2));
    }

    SECTION("Check specific assignment pattern exists") {
        REQUIRE(assignPatternReader->contains(stmtNum1) == true);
        REQUIRE(assignPatternReader->contains(stmtNum2) == true);
        REQUIRE(assignPatternReader->contains(999) == false); // Test for a non-existent statement number.
    }

    SECTION("Retrieve LHS and RHS of specific assignment patterns") {
        REQUIRE(assignPatternReader->getLHS(stmtNum1) == lhs1);
        REQUIRE(assignPatternReader->getRHS(stmtNum1) == rhs1);
        REQUIRE(assignPatternReader->getLHS(stmtNum2) == lhs2);
        REQUIRE(assignPatternReader->getRHS(stmtNum2) == rhs2);
    }

    SECTION("Retrieve statement numbers by LHS") {
        auto stmtsWithLHS = assignPatternReader->getStatementNumbersWithLHS(lhs1);
        REQUIRE(stmtsWithLHS.find(stmtNum1) != stmtsWithLHS.end());
        REQUIRE(stmtsWithLHS.find(stmtNum2) == stmtsWithLHS.end()); // `lhs2` should not be found in the result set for `lhs1`.
    }

    SECTION("Retrieve statement numbers by RHS (including partial matches)") {
        auto stmtsWithRHS = assignPatternReader->getStatementNumbersWithRHS(rhs2);
        auto stmtsWithPartialRHS = assignPatternReader->getStatementNumbersWithPartialRHS("x");
        REQUIRE(stmtsWithRHS.find(stmtNum2) != stmtsWithRHS.end());
        REQUIRE(stmtsWithPartialRHS.size() >= 1); // Since `rhs1` and `rhs2` both contain `x`, at least one match is expected.
    }

    SECTION("Check if AssignPatternStore is empty after clearing") {
        assignPatternWriter->clear();
        REQUIRE(assignPatternReader->isEmpty() == true);
    }

}
