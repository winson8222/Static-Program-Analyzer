#include "catch.hpp"
#include <memory>
#include <string>
#include "pkb/PKBManager.h"
#include "../Utils.h"

TEST_CASE("qps/QueryProcessingSubsystem: ModifiesSReader Integration Test") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto modifiesWriter = pkbManager->getPKBWriterManager()->getModifiesSWriter();
    auto statementWriter = pkbManager->getPKBWriterManager()->getStatementWriter();

    // Setup PKB with ModifiesS relationships
    modifiesWriter->clear();
    statementWriter->clear();

    // Assuming statements and their modifications
    modifiesWriter->addModifiesS(1, "x");
    modifiesWriter->addModifiesS(2, "y");
    modifiesWriter->addModifiesS(3, "z");
    modifiesWriter->addModifiesS(4, "x");

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);

    auto pkbReaderManager = pkbManager->getPKBReaderManager();

    SECTION("Verify ModifiesS relationships via QPS") {
        // Verify that statement 1 modifies variable "x"
        std::string query1 = "stmt s; variable v; Select s such that Modifies(s, \"x\")";
        auto results1 = Utils::getResultsFromQuery(query1, pkbReaderManager);
        std::unordered_set<std::string> expectedResults1 = {"1", "4"}; // Statements that modify "x"
        REQUIRE(results1 == expectedResults1);

        // Verify that variable "y" is modified by statement 2
        std::string query2 = "variable v; Select v such that Modifies(2, v)";
        auto results2 = Utils::getResultsFromQuery(query2, pkbReaderManager);
        std::unordered_set<std::string> expectedResults2 = {"y"}; // Variables modified by statement 2
        REQUIRE(results2 == expectedResults2);
    }

    SECTION("Verify non-existent ModifiesS relationships via QPS") {
        // Test for a non-existent modification relationship
        std::string queryNonExistent = "stmt s; variable v; Select s such that Modifies(s, \"nonExistentVar\")";
        auto resultsNonExistent = Utils::getResultsFromQuery(queryNonExistent, pkbReaderManager);
        REQUIRE(resultsNonExistent.empty()); // Expect no results for a non-existent variable
    }

    SECTION("Test ModifiesS with multiple statements and variables via QPS") {
        // Verify all statements that modify any variable
        std::string queryAll = "stmt s; variable v; Select s such that Modifies(s, v)";
        auto resultsAll = Utils::getResultsFromQuery(queryAll, pkbReaderManager);
        std::unordered_set<std::string> expectedResultsAll = {"1", "2", "3", "4"}; // All statements that modify a variable
        REQUIRE(resultsAll == expectedResultsAll);
    }

}
