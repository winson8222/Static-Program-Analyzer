#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "../Utils.h" // Assuming Utils.h is available for utility functions

// Fixture class for setting up PKB and Read tests
class ReadReaderFixture {
public:
    std::shared_ptr<PKBManager> pkbManager;
    std::shared_ptr<ReadWriter> readWriter;

    ReadReaderFixture() : pkbManager(std::make_shared<PKBManager>()) {
        readWriter = pkbManager->getPKBWriterManager()->getReadWriter();
        // Clearing previous data for a clean state
        readWriter->clear();
    }

    void populateReadStatements() {
        // Populating "read" statements for retrieval tests
        readWriter->insertRead(4);
        readWriter->insertRead(8);
    }
};

TEST_CASE_METHOD(ReadReaderFixture, "qps/QueryProcessingSubsystem: ReadReader Integration Test", "[QPS][PKB][Read]") {
    populateReadStatements();

    SECTION("Verify retrieval of all 'read' statement numbers via QPS") {
        std::string query = "read r; Select r";
        auto results = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
        std::unordered_set<std::string> expectedResults = {"4", "8"};
        REQUIRE(results == expectedResults);
    }

//    SECTION("Check for the existence of a specific 'read' statement") {
//        std::string queryExists = "read r; Select BOOLEAN such that Uses(r, _)";
//        auto resultsExists = Utils::getResultsFromQuery(queryExists, pkbManager->getPKBReaderManager());
//        // Assuming 'Uses' is just a placeholder for any relevant condition to check existence
//        REQUIRE(!resultsExists.empty()); // Adjust based on actual data and query capabilities
//    }
//
//    SECTION("Test for a non-existent 'read' statement") {
//        std::string queryNonExistent = "read r; Select BOOLEAN such that Uses(r, \"nonExistentVar\")";
//        auto resultsNonExistent = Utils::getResultsFromQuery(queryNonExistent, pkbManager->getPKBReaderManager());
//        REQUIRE(resultsNonExistent.find("FALSE") != resultsNonExistent.end());
//    }

}
