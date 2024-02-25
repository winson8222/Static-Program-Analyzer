#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "../Utils.h" // Assuming Utils.h is available for utility functions

// Fixture class for setting up PKB and While tests
class WhileReaderFixture {
public:
    std::shared_ptr<PKBManager> pkbManager;
    std::shared_ptr<WhileWriter> whileWriter;

    WhileReaderFixture() : pkbManager(std::make_shared<PKBManager>()) {
        whileWriter = pkbManager->getPKBWriterManager()->getWhileWriter();
        // Clearing previous data for a clean state
        whileWriter->clear();

    }

    void populateWhileStatements() {
        // Populating "while" statements for retrieval tests
        whileWriter->insertWhile(1);
        whileWriter->insertWhile(5);

    }
};

TEST_CASE_METHOD(WhileReaderFixture, "qps/QueryProcessingSubsystem: WhileReader Integration Test", "[QPS][PKB][While]") {
    populateWhileStatements();

    SECTION("Verify retrieval of all 'while' statement numbers via QPS") {
        std::string query = "while w; Select w";
        auto results = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
        std::unordered_set<std::string> expectedResults = {"1", "5"};
        REQUIRE(results == expectedResults);
    }

    SECTION("Check specific 'while' statements exist via QPS") {
        

        std::string queryNonExistentWhile = "while w; Select w such that Follows(1, w)";
        auto resultNonExistentWhile = Utils::getResultsFromQuery(queryNonExistentWhile, pkbManager->getPKBReaderManager());
        REQUIRE(resultNonExistentWhile.empty());
    }

    SECTION("Verify store is cleared correctly via QPS") {
        whileWriter->clear(); // Clear all 'while' statements
        std::string query = "while w; Select w";
        auto resultsAfterClear = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
        REQUIRE(resultsAfterClear.empty());
    }
}
