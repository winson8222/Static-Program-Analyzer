#include "catch.hpp"
#include "pkb/stores/relationships/types/ModifiesPStore.h"
#include "pkb/readers/relationships/ModifiesPReader.h"

TEST_CASE("pkb/readers/relationships/ModifiesPReader") {
    auto modifiesPStore = std::make_shared<ModifiesPStore>();
    ModifiesPReader modifiesPReader(modifiesPStore);

    SECTION("isEmpty: Empty on initialization") {
        REQUIRE(modifiesPReader.isEmpty());
    }

    // Assume these methods exist to add modifiesP relationships directly to the store for testing
    modifiesPStore->addRelationship("procedureX", "variableA");
    modifiesPStore->addRelationship("procedureX", "variableB");
    modifiesPStore->addRelationship("procedureY", "variableA");

    SECTION("isEmpty: Not empty after adding relationships") {
        REQUIRE_FALSE(modifiesPReader.isEmpty());
    }

    SECTION("doesProcModifyVariable") {
        REQUIRE(modifiesPReader.doesProcModifyVariable("procedureX", "variableA"));
        REQUIRE(modifiesPReader.doesProcModifyVariable("procedureX", "variableB"));
        REQUIRE(modifiesPReader.doesProcModifyVariable("procedureY", "variableA"));
        REQUIRE_FALSE(modifiesPReader.doesProcModifyVariable("procedureY", "variableB")); // This relationship does not exist
    }

    SECTION("getAllProcsThatModifyVariable") {
        auto variablesModifiedByProcedureX = modifiesPReader.getAllVariablesModifiedByProc("procedureX");
        REQUIRE(variablesModifiedByProcedureX.size() == 2);
        REQUIRE(variablesModifiedByProcedureX.count("variableA"));
        REQUIRE(variablesModifiedByProcedureX.count("variableB"));
    }

    SECTION("getAllVariablesModifiedByProc") {
        auto proceduresModifyingVariableA = modifiesPReader.getAllProcsThatModifyVariable("variableA");
        REQUIRE(proceduresModifyingVariableA.size() == 2); // Both procedures modify variableA
        REQUIRE(proceduresModifyingVariableA.count("procedureX"));
        REQUIRE(proceduresModifyingVariableA.count("procedureY"));
    }

    SECTION("getAllProcsThatModifyAnyVariable") {
        auto allModifyingProcedures = modifiesPReader.getAllProcsThatModifyAnyVariable();
        REQUIRE(allModifyingProcedures.size() == 2); // "procedureX" and "procedureY"
        REQUIRE(allModifyingProcedures.count("procedureX"));
        REQUIRE(allModifyingProcedures.count("procedureY"));
    }

    SECTION("getAllVariablesModifiedByAnyProc") {
        auto allModifiedVariables = modifiesPReader.getAllVariablesModifiedByAnyProc();
        REQUIRE(allModifiedVariables.size() == 2); // "variableA" and "variableB"
        REQUIRE(allModifiedVariables.count("variableA"));
        REQUIRE(allModifiedVariables.count("variableB"));
    }
}