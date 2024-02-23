#include "catch.hpp"
#include "pkb/stores/relationships/types/ModifiesSStore.h"
#include "pkb/readers/relationships/ModifiesSReader.h"

TEST_CASE("pkb/readers/relationships/ModifiesSReader") {
    auto modifiesSStore = std::make_shared<ModifiesSStore>();
    ModifiesSReader modifiesSReader(modifiesSStore);

    SECTION("isEmpty: Empty on initialization") {
        REQUIRE(modifiesSReader.isEmpty());
    }
    // Assuming methods to add modifies relationships directly for testing
    modifiesSStore->addRelationship(1, "variableX"); // Statement 1 modifies variableX
    modifiesSStore->addRelationship(2, "variableY"); // Statement 2 modifies variableY
    modifiesSStore->addRelationship(1, "variableZ"); // Statement 1 also modifies variableZ


    SECTION("isEmpty: Not empty after adding relationships") {
        REQUIRE_FALSE(modifiesSReader.isEmpty());
    }

    SECTION("doesStmtModifyVariable") {
      REQUIRE(modifiesSReader.doesStmtModifyVariable(1, "variableX"));
      REQUIRE(modifiesSReader.doesStmtModifyVariable(2, "variableY"));
      REQUIRE(modifiesSReader.doesStmtModifyVariable(1, "variableZ"));
      REQUIRE_FALSE(modifiesSReader.doesStmtModifyVariable(2, "variableX")); // This relationship does not exist
    }

    SECTION("getAllVariablesModifiedByStmt") {
      auto variablesModifiedByStatement1 = modifiesSReader.getAllVariablesModifiedByStmt(1);
      REQUIRE(variablesModifiedByStatement1.size() == 2);
      REQUIRE(variablesModifiedByStatement1.count("variableX"));
      REQUIRE(variablesModifiedByStatement1.count("variableZ"));
    }

    SECTION("getAllStmtsThatModifyVariable") {
      auto statementsModifyingVariableX = modifiesSReader.getAllStmtsThatModifyVariable("variableX");
      REQUIRE(statementsModifyingVariableX.size() == 1); // Only statement 1 modifies variableX
      REQUIRE(statementsModifyingVariableX.count(1));
    }

    SECTION("getAllStmtsThatModifyAnyVariable") {
      auto allModifyingStatements = modifiesSReader.getAllStmtsThatModifyAnyVariable();
      REQUIRE(allModifyingStatements.size() == 2); // Statements 1 and 2
      REQUIRE(allModifyingStatements.count(1));
      REQUIRE(allModifyingStatements.count(2));
    }

    SECTION("getAllVariablesModifiedByAnyStmt") {
      auto allModifiedVariables = modifiesSReader.getAllVariablesModifiedByAnyStmt();
      REQUIRE(allModifiedVariables.size() == 3); // "variableX" and "variableY" and "variableZ"
      REQUIRE(allModifiedVariables.count("variableX"));
      REQUIRE(allModifiedVariables.count("variableY"));
      REQUIRE(allModifiedVariables.count("variableZ"));
    }

}
