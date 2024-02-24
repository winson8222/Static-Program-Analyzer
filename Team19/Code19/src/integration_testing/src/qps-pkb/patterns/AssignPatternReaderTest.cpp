#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

#include "memory"
#include "commons/ShuntingYard.h"
#include "../Utils.h"

TEST_CASE("qps/QueryProcessingSubsystem: AssignPatternReader") {

    auto pkbManager = std::make_shared<PKBManager>();
    auto assignPatternWriter = pkbManager->getPKBWriterManager()->getAssignPatternWriter();
    auto pkbReaderManager = pkbManager->getPKBReaderManager();
    auto variableWriter = pkbManager->getPKBWriterManager()->getVariableWriter();
    auto assignWriter = pkbManager->getPKBWriterManager()->getAssignWriter();

    // Prepare the environment: Clear the store before populating it to ensure a clean state.
    assignPatternWriter->clear();

    // Populating assignment patterns for retrieval tests.
    int stmtNum1 = 1, stmtNum2 = 2;
    std::string lhs1 = "x", rhs1 = "y + 1";
    std::string lhs2 = "z", rhs2 = "x * 2";
    std::string y = "y";
    variableWriter->insertVariable(lhs1);
    variableWriter->insertVariable(lhs2);
    variableWriter->insertVariable(y);
    assignPatternWriter->addAssignPattern(stmtNum1, lhs1, ShuntingYard::convertToPostfix(rhs1));
    assignPatternWriter->addAssignPattern(stmtNum2, lhs2, ShuntingYard::convertToPostfix(rhs2));
    assignWriter->insertAssign(stmtNum1);
    assignWriter->insertAssign(stmtNum2);

    SECTION("Retrieve All RHS") {
        std::unordered_set<std::string> expectedLhs = {lhs1, lhs2};
        std::string query = "variable v; assign a; Select v pattern a(v, _)";
        auto result = Utils::getResultsFromQuery(query, pkbReaderManager);
        REQUIRE(result == expectedLhs);
    }
}
