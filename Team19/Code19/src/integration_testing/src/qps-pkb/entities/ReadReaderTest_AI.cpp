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


}
