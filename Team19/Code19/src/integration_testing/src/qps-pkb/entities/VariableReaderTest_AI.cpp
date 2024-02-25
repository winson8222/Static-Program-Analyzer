#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "../Utils.h" // Assuming Utils.h is available for utility functions

// Fixture class for setting up PKB and Variable tests
class VariableReaderFixture {
public:
    std::shared_ptr<PKBManager> pkbManager;
    std::shared_ptr<VariableWriter> variableWriter;

    VariableReaderFixture() : pkbManager(std::make_shared<PKBManager>()) {
        variableWriter = pkbManager->getPKBWriterManager()->getVariableWriter();
        // Clearing previous data for a clean state
        variableWriter->clear();
    }

    void populateVariables() {
        std::string varX = "x";
        std::string varY = "y";
        std::string varZ = "z";
        std::string varRead = "read"; // Example of a keyword as a variable name

        // Populating assignment patterns for retrieval tests
        variableWriter->insertVariable(varX);
        variableWriter->insertVariable(varY);
        variableWriter->insertVariable(varZ);
        variableWriter->insertVariable(varRead);

    }

};

TEST_CASE_METHOD(VariableReaderFixture, "qps/QueryProcessingSubsystem: VariableReader Integration Test", "[QPS][PKB][Variable]") {
    populateVariables();

    auto variableReader = pkbManager->getPKBReaderManager()->getVariableReader();

    SECTION("Verify retrieval of all variables via QPS") {
        std::string query = "variable v; Select v";
        auto results = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
        std::unordered_set<std::string> expectedResults = {"x", "y", "z", "read"};
        REQUIRE(results == expectedResults);
    }



    SECTION("Verify store is cleared correctly via QPS") {
        variableWriter->clear(); // Clear all variables
        std::string query = "variable v; Select v";
        auto resultsAfterClear = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
        REQUIRE(resultsAfterClear.empty());
    }
}
