#include "catch.hpp"
#include "pkb/stores/relationships/types/ModifiesPStore.h"

/**
 * Unit tests for the ModifiesPStore class.
 *
 * Tests the functionality of managing "Modifies" relationships for procedures,
 * focusing on the ability to track which variables are modified by which procedures.
 * The ModifiesPStore class is tasked with recording and querying these relationships,
 * ensuring that modifications by procedures to variables are accurately tracked and accessible.
 */
TEST_CASE("ModifiesPStore Functionality") {
    // Initialize ModifiesPStore instance for testing.
    ModifiesPStore modifiesPStore;

    // Test adding "Modifies" relationships and verifying their existence.
    SECTION("Add and Check Modifies Relationships for Procedures") {
        // Add "Modifies" relationships between procedures and variables.
        modifiesPStore.addRelationship("main", "x");
        modifiesPStore.addRelationship("update", "y");
        modifiesPStore.addRelationship("compute", "z");

        // Verify that the added relationships are correctly identified.
        REQUIRE(modifiesPStore.hasRelationship("main", "x")); // "main" procedure modifies variable "x".
        REQUIRE(modifiesPStore.hasRelationship("update", "y")); // "update" procedure modifies variable "y".
        REQUIRE(modifiesPStore.hasRelationship("compute", "z")); // "compute" procedure modifies variable "z".

        // Ensure that a non-existent relationship returns false.
        REQUIRE_FALSE(modifiesPStore.hasRelationship("main", "z")); // "main" does not modify variable "z".
    }

        // Test retrieving procedures that modify a specific variable.
    SECTION("Retrieve Procedures Modifying a Specific Variable") {
        // Add "Modifies" relationships between procedures and variables.
        modifiesPStore.addRelationship("main", "x");
        modifiesPStore.addRelationship("finalize", "x");

        // Verify retrieval of all procedures that modify the variable "x".
        auto proceduresModifyingX = modifiesPStore.getRelationshipsByValue("x");
        auto expectedProcedures = std::unordered_set<std::string>{"main", "finalize"};

        REQUIRE(proceduresModifyingX == expectedProcedures); // Both "main" and "finalize" modify "x".
    }

        // Test retrieving variables modified by a specific procedure.
    SECTION("Retrieve Variables Modified by a Procedure") {
        // Add "Modifies" relationships for a single procedure.
        modifiesPStore.addRelationship("main", "x");
        modifiesPStore.addRelationship("main", "y");

        // Verify retrieval of all variables modified by the "main" procedure.
        auto variablesModifiedByMain = modifiesPStore.getRelationshipsByKey("main");
        auto expectedVariables = std::unordered_set<std::string>{"x", "y"};

        REQUIRE(variablesModifiedByMain == expectedVariables); // "main" modifies variables "x" and "y".
    }

        // Test the ability to clear all "Modifies" relationships from the store.
    SECTION("Clear All Modifies Relationships") {
        // Initially, the store should be empty.
        REQUIRE(modifiesPStore.isEmpty());

        // Adding a relationship should change the store's state to non-empty.
        modifiesPStore.addRelationship("main", "x");
        REQUIRE_FALSE(modifiesPStore.isEmpty());

        // Clearing the store should reset its state to empty.
        modifiesPStore.clear();
        REQUIRE(modifiesPStore.isEmpty());
    }
}
