#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "../Utils.h" // Assuming Utils.h is available for utility functions

// Fixture class for setting up PKB and Statement tests
class StatementReaderFixture {
public:
    std::shared_ptr<PKBManager> pkbManager;
    std::shared_ptr<StatementWriter> statementWriter;

    StatementReaderFixture() : pkbManager(std::make_shared<PKBManager>()) {
        statementWriter = pkbManager->getPKBWriterManager()->getStatementWriter();
        // Clearing previous data for a clean state
        statementWriter->clear();
    }

    void populateStatements() {
        // Populating statements for retrieval tests
        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
    }
};

TEST_CASE_METHOD(StatementReaderFixture, "qps/QueryProcessingSubsystem: StatementReader Integration Test", "[QPS][PKB][Statement]") {
    populateStatements();

    SECTION("Verify retrieval of all statements via QPS") {
        std::string query = "stmt s; Select s";
        auto results = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
        std::unordered_set<std::string> expectedResults = {"1", "2", "3"};
        REQUIRE(results == expectedResults);
    }

    SECTION("Check specific statements exist via QPS") {
        std::string queryStmt1 = "stmt s; Select s such that Modifies(_, s)";
        auto resultStmt1 = Utils::getResultsFromQuery(queryStmt1, pkbManager->getPKBReaderManager());
        REQUIRE(resultStmt1.find("1") != resultStmt1.end());

        std::string queryNonExistentStmt = "stmt s; Select s such that Follows(1, s)";
        auto resultNonExistentStmt = Utils::getResultsFromQuery(queryNonExistentStmt, pkbManager->getPKBReaderManager());
        REQUIRE(resultNonExistentStmt.empty());
    }

    SECTION("Verify store is cleared correctly via QPS") {
        statementWriter->clear(); // Clear all statements
        std::string query = "stmt s; Select s";
        auto resultsAfterClear = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
        REQUIRE(resultsAfterClear.empty());
    }

}
