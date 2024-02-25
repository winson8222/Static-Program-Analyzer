#include "catch.hpp"
#include <memory>
#include <string>
#include "pkb/PKBManager.h"
#include "../Utils.h"

TEST_CASE("qps/QueryProcessingSubsystem: UsesSReader Integration Test") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto usesWriter = pkbManager->getPKBWriterManager()->getUsesSWriter();
    auto statementWriter = pkbManager->getPKBWriterManager()->getStatementWriter();

    // Setup PKB with UsesS relationships
    usesWriter->clear();
    statementWriter->clear();

    // Assuming statements and their usages
    usesWriter->addUsesS(1, "a");
    usesWriter->addUsesS(2, "b");
    usesWriter->addUsesS(3, "c");
    usesWriter->addUsesS(4, "a");

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);

    auto pkbReaderManager = pkbManager->getPKBReaderManager();

    SECTION("Verify UsesS relationships via QPS") {
        // Verify that statement 1 uses variable "a"
        std::string query1 = "stmt s; variable v; Select s such that Uses(s, \"a\")";
        auto results1 = Utils::getResultsFromQuery(query1, pkbReaderManager);
        std::unordered_set<std::string> expectedResults1 = {"1", "4"}; // Statements that use "a"
        REQUIRE(results1 == expectedResults1);

        // Verify that variable "b" is used by statement 2
        std::string query2 = "variable v; Select v such that Uses(2, v)";
        auto results2 = Utils::getResultsFromQuery(query2, pkbReaderManager);
        std::unordered_set<std::string> expectedResults2 = {"b"}; // Variables used by statement 2
        REQUIRE(results2 == expectedResults2);
    }

    SECTION("Verify non-existent UsesS relationships via QPS") {
        // Test for a non-existent usage relationship
        std::string queryNonExistent = "stmt s; variable v; Select s such that Uses(s, \"nonExistentVar\")";
        auto resultsNonExistent = Utils::getResultsFromQuery(queryNonExistent, pkbReaderManager);
        REQUIRE(resultsNonExistent.empty()); // Expect no results for a non-existent variable
    }

    SECTION("Test UsesS with multiple statements and variables via QPS") {
        // Verify all statements that use any variable
        std::string queryAll = "stmt s; variable v; Select s such that Uses(s, v)";
        auto resultsAll = Utils::getResultsFromQuery(queryAll, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsAll = {"1", "2", "3", "4"}; // All statements that use a variable
        REQUIRE(resultsAll == expectedResultsAll);
    }

}
