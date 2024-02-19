#include "catch.hpp"
#include "pkb/PKBManager.h"
#include "pkb/stores/relationships/types/UsesPStore.h"
#include "pkb/readers/relationships/UsesPReader.h"

TEST_CASE("UsesPReader: Basic Functionality", "[UsesPReader]") {
    auto usesPStore = std::make_shared<UsesPStore>();
    UsesPReader usesPReader(usesPStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(usesPReader.isEmpty());
    }

    SECTION("Adding and checking Uses relationships for procedures") {
        // Directly add relationships to usesPStore for testing
        usesPStore->addRelationship("procedure1", "varA");
        usesPStore->addRelationship("procedure1", "varB");
        usesPStore->addRelationship("procedure2", "varA");

        REQUIRE_FALSE(usesPReader.isEmpty());
        REQUIRE(usesPReader.hasRelationship("procedure1", "varA"));
        REQUIRE(usesPReader.hasRelationship("procedure1", "varB"));
        REQUIRE(usesPReader.hasRelationship("procedure2", "varA"));
        REQUIRE_FALSE(usesPReader.hasRelationship("procedure2", "varB")); // This relationship does not exist

        auto varsUsedByProc1 = usesPReader.getRelationshipsByKey("procedure1");
        REQUIRE(varsUsedByProc1.size() == 2);
        REQUIRE(varsUsedByProc1.count("varA"));
        REQUIRE(varsUsedByProc1.count("varB"));

        auto procsUsingVarA = usesPReader.getRelationshipsByValue("varA");
        REQUIRE(procsUsingVarA.size() == 2); // Both procedures use varA
        REQUIRE(procsUsingVarA.count("procedure1"));
        REQUIRE(procsUsingVarA.count("procedure2"));

        auto allUsingProcedures = usesPReader.getKeys();
        REQUIRE(allUsingProcedures.size() == 2); // "procedure1" and "procedure2"
        REQUIRE(allUsingProcedures.count("procedure1"));
        REQUIRE(allUsingProcedures.count("procedure2"));

        auto allUsedVariables = usesPReader.getValues();
        REQUIRE(allUsedVariables.size() == 2); // "varA" and "varB"
        REQUIRE(allUsedVariables.count("varA"));
        REQUIRE(allUsedVariables.count("varB"));
    }
}
