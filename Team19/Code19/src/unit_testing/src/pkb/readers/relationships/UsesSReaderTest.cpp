#include "catch.hpp"
#include "pkb/stores/relationships/types/UsesSStore.h"
#include "pkb/readers/relationships/UsesSReader.h"

TEST_CASE("UsesSReader: Basic Functionality", "[UsesSReader]") {
    auto usesSStore = std::make_shared<UsesSStore>();
    UsesSReader usesSReader(usesSStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(usesSReader.isEmpty());
    }

    SECTION("Adding and checking Uses relationships for statements") {
        // Assume these methods exist to add uses relationships directly to the store for testing
        usesSStore->addRelationship(1, "variableX");
        usesSStore->addRelationship(2, "variableY");
        usesSStore->addRelationship(1, "variableY");

        REQUIRE_FALSE(usesSReader.isEmpty());
        REQUIRE(usesSReader.hasRelationship(1, "variableX"));
        REQUIRE(usesSReader.hasRelationship(2, "variableY"));
        REQUIRE(usesSReader.hasRelationship(1, "variableY"));
        REQUIRE_FALSE(usesSReader.hasRelationship(2, "variableX")); // This relationship does not exist

        auto variablesUsedByStmt1 = usesSReader.getRelationshipsByKey(1);
        REQUIRE(variablesUsedByStmt1.size() == 2);
        REQUIRE(variablesUsedByStmt1.count("variableX"));
        REQUIRE(variablesUsedByStmt1.count("variableY"));

        auto statementsUsingVariableY = usesSReader.getRelationshipsByValue("variableY");
        REQUIRE(statementsUsingVariableY.size() == 2); // Both statements 1 and 2 use variableY
        REQUIRE(statementsUsingVariableY.count(1));
        REQUIRE(statementsUsingVariableY.count(2));

        auto allUsingStatements = usesSReader.getKeys();
        REQUIRE(allUsingStatements.size() == 2); // Statements 1 and 2
        REQUIRE(allUsingStatements.count(1));
        REQUIRE(allUsingStatements.count(2));

        auto allUsedVariables = usesSReader.getValues();
        REQUIRE(allUsedVariables.size() == 2); // "variableX" and "variableY"
        REQUIRE(allUsedVariables.count("variableX"));
        REQUIRE(allUsedVariables.count("variableY"));
    }

}
