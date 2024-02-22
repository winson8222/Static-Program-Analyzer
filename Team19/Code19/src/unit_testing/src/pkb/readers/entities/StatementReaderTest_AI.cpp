#include "catch.hpp"
#include "pkb/PKBManager.h"

TEST_CASE("pkb/readers/entities/StatementReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto statementReader = pkbManager->getPKBReaderManager()->getStatementReader();
    auto statementWriter = pkbManager->getPKBWriterManager()->getStatementWriter();

    SECTION("getAllStatements: Empty") {
        REQUIRE(statementReader->getAllStatements().empty());
    }

    SECTION("getAllStatements: Non-empty") {
        statementWriter->insertStatement(5);
        statementWriter->insertStatement(6);
        REQUIRE(statementReader->getAllStatements() == std::unordered_set<int>{5, 6});
        statementWriter->clear();
    }
}
