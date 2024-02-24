#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

// Defines a setup for Assignment Pattern Matching tests to avoid repetition
class AssignPatternMatchingFixture {
public:
    std::shared_ptr<PKBManager> pkbManager;
    std::shared_ptr<AssignPatternWriter> assignPatternWriter;
    std::shared_ptr<AssignPatternReader> assignPatternReader;

    AssignPatternMatchingFixture() : pkbManager(std::make_shared<PKBManager>()) {
        assignPatternWriter = pkbManager->getPKBWriterManager()->getAssignPatternWriter();
        assignPatternReader = pkbManager->getPKBReaderManager()->getAssignPatternReader();
        // Clearing previous data to ensure a clean start for each test
        assignPatternWriter->clear();
    }

    void populatePatterns() {
        // Populating PKB with various assignment patterns for comprehensive testing
        assignPatternWriter->addAssignPattern(1, "x", "v + x * y + z * t");
        assignPatternWriter->addAssignPattern(2, "y", "x - 5");
        assignPatternWriter->addAssignPattern(3, "z", "y * 2 + x / 5");
        // Additional patterns can be added here
    }
};

TEST_CASE_METHOD(AssignPatternMatchingFixture, "qps/QueryProcessingSubsystem: Assignment Pattern Matching", "[QPS][PKB][AssignPattern]") {
    populatePatterns();

    SECTION("Verify pattern retrieval for a specific statement") {
        REQUIRE(assignPatternReader->contains(1) == true);
        auto pattern = assignPatternReader->getPattern(1);
        REQUIRE(pattern.first == "x");
        REQUIRE(pattern.second == "v + x * y + z * t");
    }

    SECTION("Retrieve All Statement Numbers with Specific RHS") {
        auto stmtsWithRHS = assignPatternReader->getStatementNumbersWithRHS("v + x * y + z * t");
        REQUIRE(stmtsWithRHS.find(1) != stmtsWithRHS.end());
    }

    SECTION("Matching with Variable as First Argument and Complex Expression Matches") {
        // Combining related tests to reduce repetition and improve clarity
        auto stmtsWithX = assignPatternReader->getStatementNumbersWithLHS("x");
        REQUIRE(stmtsWithX.size() == 1);
        REQUIRE(stmtsWithX.find(1) != stmtsWithX.end());

        auto stmtsWithComplexRHS = assignPatternReader->getStatementNumbersWithRHS("y * 2 + x / 5");
        REQUIRE(stmtsWithComplexRHS.size() == 1);
        REQUIRE(stmtsWithComplexRHS.find(3) != stmtsWithComplexRHS.end());
    }

}
