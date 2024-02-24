#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "../Utils.h" // Assuming Utils.h is available for utility functions

// Fixture class for setting up PKB and If statement tests
class IfStatementFixture {
public:
    std::shared_ptr<PKBManager> pkbManager;
    std::shared_ptr<IfWriter> ifWriter;

    IfStatementFixture() : pkbManager(std::make_shared<PKBManager>()) {
        ifWriter = pkbManager->getPKBWriterManager()->getIfWriter();
        // Clearing previous data for a clean state
        ifWriter->clear();
    }

    void populateIfs() {
        // Populating if statements for retrieval tests
        ifWriter->insertIf(2);
        ifWriter->insertIf(6);
        // Additional if statements can be added here
    }
};

TEST_CASE_METHOD(IfStatementFixture, "qps/QueryProcessingSubsystem: IfReader Integration Test", "[QPS][PKB][IfReader]") {
    populateIfs();

    SECTION("Retrieve All If Statement Numbers") {
        std::string query = "if ifs; Select ifs";
        auto results = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
        std::unordered_set<std::string> expectedResults = {"2", "6"};
        REQUIRE(results == expectedResults);
    }

}
