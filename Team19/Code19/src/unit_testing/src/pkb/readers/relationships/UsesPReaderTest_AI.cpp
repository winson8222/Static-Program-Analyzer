#include "catch.hpp"
#include "pkb/PKBManager.h"
#include "pkb/stores/relationships/types/UsesPStore.h"
#include "pkb/readers/relationships/UsesPReader.h"

TEST_CASE("pkb/readers/relationships/UsesPReader") {
    auto usesPStore = std::make_shared<UsesPStore>();
    UsesPReader usesPReader(usesPStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(usesPReader.isEmpty());
    }

    // Directly add relationships to usesPStore for testing
    usesPStore->addRelationship("procedure1", "varA");
    usesPStore->addRelationship("procedure1", "varB");
    usesPStore->addRelationship("procedure2", "varA");

    SECTION("isEmpty: Not empty after adding relationships") {
        REQUIRE_FALSE(usesPReader.isEmpty());
    }


    SECTION("doesProcUseVariable") {
        REQUIRE(usesPReader.doesProcUseVariable("procedure1", "varA"));
        REQUIRE(usesPReader.doesProcUseVariable("procedure1", "varB"));
        REQUIRE(usesPReader.doesProcUseVariable("procedure2", "varA"));
        REQUIRE_FALSE(usesPReader.doesProcUseVariable("procedure2", "varB")); // This relationship does not exist
    }

    SECTION("getAllProcsThatUseVariable") {
        auto variablesUsedByProcedure1 = usesPReader.getAllProcsThatUseVariable("varA");
        REQUIRE(variablesUsedByProcedure1.size() == 2);
        REQUIRE(variablesUsedByProcedure1.count("procedure1"));
        REQUIRE(variablesUsedByProcedure1.count("procedure2"));
    }

    SECTION("getAllVariablesUsedByProc") {
        auto proceduresUsingVarA = usesPReader.getAllVariablesUsedByProc("procedure1");
        REQUIRE(proceduresUsingVarA.size() == 2); // Both procedures use varA
        REQUIRE(proceduresUsingVarA.count("varA"));
        REQUIRE(proceduresUsingVarA.count("varB"));
    }

    SECTION("getAllProcsThatUseAnyVariable") {
        auto allUsingProcedures = usesPReader.getAllProcsThatUseAnyVariable();
        REQUIRE(allUsingProcedures.size() == 2); // "procedure1" and "procedure2"
        REQUIRE(allUsingProcedures.count("procedure1"));
        REQUIRE(allUsingProcedures.count("procedure2"));
    }

    SECTION("getAllVariablesUsedByAnyProc") {
        auto allUsedVariables = usesPReader.getAllVariablesUsedByAnyProc();
        REQUIRE(allUsedVariables.size() == 2); // "varA" and "varB"
        REQUIRE(allUsedVariables.count("varA"));
        REQUIRE(allUsedVariables.count("varB"));
    }
}
