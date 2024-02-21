#include "catch.hpp"
#include "pkb/stores/relationships/types/ModifiesSStore.h"
#include "pkb/readers/relationships/ModifiesSReader.h"

TEST_CASE("ModifiesSReader: Basic Functionality", "[ModifiesSReader]") {
    auto modifiesSStore = std::make_shared<ModifiesSStore>();
    ModifiesSReader modifiesSReader(modifiesSStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(modifiesSReader.isEmpty());
    }

    SECTION("Adding and checking Modifies relationships for statements") {
        // Assuming methods to add modifies relationships directly for testing
        modifiesSStore->addRelationship(1, "variableX"); // Statement 1 modifies variableX
        modifiesSStore->addRelationship(2, "variableY"); // Statement 2 modifies variableY
        modifiesSStore->addRelationship(1, "variableZ"); // Statement 1 also modifies variableZ

        REQUIRE_FALSE(modifiesSReader.isEmpty());
        REQUIRE(modifiesSReader.hasRelationship(1, "variableX"));
        REQUIRE(modifiesSReader.hasRelationship(2, "variableY"));
        REQUIRE(modifiesSReader.hasRelationship(1, "variableZ"));
        REQUIRE_FALSE(modifiesSReader.hasRelationship(2, "variableX")); // This relationship does not exist

        auto variablesModifiedByStatement1 = modifiesSReader.getRelationshipsByKey(1);
        REQUIRE(variablesModifiedByStatement1.size() == 2);
        REQUIRE(variablesModifiedByStatement1.count("variableX"));
        REQUIRE(variablesModifiedByStatement1.count("variableZ"));

        auto statementsModifyingVariableX = modifiesSReader.getRelationshipsByValue("variableX");
        REQUIRE(statementsModifyingVariableX.size() == 1); // Only statement 1 modifies variableX
        REQUIRE(statementsModifyingVariableX.count(1));

        auto allModifyingStatements = modifiesSReader.getKeys();
        REQUIRE(allModifyingStatements.size() == 2); // Statements 1 and 2
        REQUIRE(allModifyingStatements.count(1));
        REQUIRE(allModifyingStatements.count(2));

        auto allModifiedVariables = modifiesSReader.getValues();
        REQUIRE(allModifiedVariables.size() == 3); // "variableX" and "variableY" and "variableZ"
        REQUIRE(allModifiedVariables.count("variableX"));
        REQUIRE(allModifiedVariables.count("variableY"));
        REQUIRE(allModifiedVariables.count("variableZ"));
    }

}
