#include "catch.hpp"
#include "pkb/stores/relationships/types/UsesSStore.h"
#include "pkb/readers/relationships/UsesSReader.h"

TEST_CASE("pkb/readers/relationships/UsesSReader") {
    auto usesSStore = std::make_shared<UsesSStore>();
    UsesSReader usesSReader(usesSStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(usesSReader.isEmpty());
    }

    // Assume these methods exist to add uses relationships directly to the store for testing
    usesSStore->addRelationship(1, "variableX");
    usesSStore->addRelationship(2, "variableY");
    usesSStore->addRelationship(1, "variableY");

    SECTION("isEmpty: Not empty after adding relationships") {
        REQUIRE_FALSE(usesSReader.isEmpty());
    }

    SECTION("doesStmtUseVariable") {
      REQUIRE(usesSReader.doesStmtUseVariable(1, "variableX"));
      REQUIRE(usesSReader.doesStmtUseVariable(2, "variableY"));
      REQUIRE(usesSReader.doesStmtUseVariable(1, "variableY"));
      REQUIRE_FALSE(usesSReader.doesStmtUseVariable(2, "variableX")); // This relationship does not exist
    }

    SECTION("getAllVariablesUsedByStmt") {
      auto variablesUsedByStmt1 = usesSReader.getAllVariablesUsedByStmt(1);
      REQUIRE(variablesUsedByStmt1.size() == 2);
      REQUIRE(variablesUsedByStmt1.count("variableX"));
      REQUIRE(variablesUsedByStmt1.count("variableY"));
    }

    SECTION("getAllStmtsThatUseVariable") {
      auto statementsUsingVariableY = usesSReader.getAllStmtsThatUseVariable("variableY");
      REQUIRE(statementsUsingVariableY.size() == 2); // Both statements 1 and 2 use variableY
      REQUIRE(statementsUsingVariableY.count(1));
      REQUIRE(statementsUsingVariableY.count(2));
    }

    SECTION("getAllStmtsThatUseAnyVariable") {
      auto allUsingStatements = usesSReader.getAllStmtsThatUseAnyVariable();
      REQUIRE(allUsingStatements.size() == 2); // Statements 1 and 2
      REQUIRE(allUsingStatements.count(1));
      REQUIRE(allUsingStatements.count(2));
    }

    SECTION("getAllVariablesUsedByAnyStmt") {
      auto allUsedVariables = usesSReader.getAllVariablesUsedByAnyStmt();
      REQUIRE(allUsedVariables.size() == 2); // "variableX" and "variableY"
      REQUIRE(allUsedVariables.count("variableX"));
      REQUIRE(allUsedVariables.count("variableY"));
    }
}
