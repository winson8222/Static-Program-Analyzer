#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "pkb/writers/patterns/AssignPatternWriter.h"
#include "pkb/readers/patterns/AssignPatternReader.h"
#include "../Utils.h" // Assuming Utils.h is available for utility functions

// Fixture class for setting up PKB and Assignment Pattern tests
class AssignPatternMatchingFixture {
public:
    std::shared_ptr<PKBManager> pkbManager;
    std::shared_ptr<AssignPatternWriter> assignPatternWriter;
    std::shared_ptr<VariableWriter> variableWriter;
    std::shared_ptr<AssignWriter> assignWriter;

    AssignPatternMatchingFixture() : pkbManager(std::make_shared<PKBManager>()) {
        assignPatternWriter = pkbManager->getPKBWriterManager()->getAssignPatternWriter();
        variableWriter = pkbManager->getPKBWriterManager()->getVariableWriter();
        assignWriter = pkbManager->getPKBWriterManager()->getAssignWriter();
        // Clearing previous data for a clean state
        assignPatternWriter->clear();
    }

    void populatePatterns() {
        // Define variables as non-const strings
        std::string varX = "x";
        std::string varY = "y";
        std::string varZ = "z";

        // Populating assignment patterns for retrieval tests
        variableWriter->insertVariable(varX);
        variableWriter->insertVariable(varY);
        variableWriter->insertVariable(varZ);
        assignPatternWriter->addAssignPattern(1, varX, "y");
        assignPatternWriter->addAssignPattern(2, varZ, "x");
        assignWriter->insertAssign(1);
        assignWriter->insertAssign(2);
    }

};

TEST_CASE_METHOD(AssignPatternMatchingFixture, "qps/QueryProcessingSubsystem: AssignPatternReader Integration Test", "[QPS][PKB][AssignPattern]") {
    populatePatterns();

    SECTION("Retrieve All RHS") {
        std::unordered_set<std::string> expectedLhs = {"x", "z"};
        std::string query = "variable v; assign a; Select v pattern a(v, _)";
        auto result = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
        REQUIRE(result == expectedLhs);
    }

    SECTION("Pattern Matching with Specific RHS") {
        std::string query1 = "assign a; Select a pattern a(_, \"y\")";
        auto results1 = Utils::getResultsFromQuery(query1, pkbManager->getPKBReaderManager());
        REQUIRE(results1 == std::unordered_set<std::string>{"1"});

        std::string query2 = "assign a; Select a pattern a(_, \"x\")";
        auto results2 = Utils::getResultsFromQuery(query2, pkbManager->getPKBReaderManager());
        REQUIRE(results2 == std::unordered_set<std::string>{"2"});
    }

}
