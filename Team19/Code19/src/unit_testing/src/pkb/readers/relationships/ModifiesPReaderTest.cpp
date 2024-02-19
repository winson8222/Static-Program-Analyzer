#include "catch.hpp"
#include "pkb/stores/relationships/types/ModifiesPStore.h"
#include "pkb/readers/relationships/ModifiesPReader.h"

TEST_CASE("ModifiesPReader: Basic Functionality", "[ModifiesPReader]") {
    auto modifiesPStore = std::make_shared<ModifiesPStore>();
    ModifiesPReader modifiesPReader(modifiesPStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(modifiesPReader.isEmpty());
    }

    SECTION("Adding and checking Modifies relationships for procedures") {
        // Assume these methods exist to add modifies relationships directly to the store for testing
        modifiesPStore->addRelationship("procedureX", "variableA");
        modifiesPStore->addRelationship("procedureX", "variableB");
        modifiesPStore->addRelationship("procedureY", "variableA");

        REQUIRE_FALSE(modifiesPReader.isEmpty());
        REQUIRE(modifiesPReader.hasRelationship("procedureX", "variableA"));
        REQUIRE(modifiesPReader.hasRelationship("procedureX", "variableB"));
        REQUIRE(modifiesPReader.hasRelationship("procedureY", "variableA"));
        REQUIRE_FALSE(modifiesPReader.hasRelationship("procedureY", "variableB")); // This relationship does not exist

        auto variablesModifiedByProcedureX = modifiesPReader.getRelationshipsByKey("procedureX");
        REQUIRE(variablesModifiedByProcedureX.size() == 2);
        REQUIRE(variablesModifiedByProcedureX.count("variableA"));
        REQUIRE(variablesModifiedByProcedureX.count("variableB"));

        auto proceduresModifyingVariableA = modifiesPReader.getRelationshipsByValue("variableA");
        REQUIRE(proceduresModifyingVariableA.size() == 2); // Both procedures modify variableA
        REQUIRE(proceduresModifyingVariableA.count("procedureX"));
        REQUIRE(proceduresModifyingVariableA.count("procedureY"));

        auto allModifyingProcedures = modifiesPReader.getKeys();
        REQUIRE(allModifyingProcedures.size() == 2); // "procedureX" and "procedureY"
        REQUIRE(allModifyingProcedures.count("procedureX"));
        REQUIRE(allModifyingProcedures.count("procedureY"));

        auto allModifiedVariables = modifiesPReader.getValues();
        REQUIRE(allModifiedVariables.size() == 2); // "variableA" and "variableB"
        REQUIRE(allModifiedVariables.count("variableA"));
        REQUIRE(allModifiedVariables.count("variableB"));
    }

}