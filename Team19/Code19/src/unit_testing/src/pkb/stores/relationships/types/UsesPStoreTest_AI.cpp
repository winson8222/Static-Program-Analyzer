#include "catch.hpp"
#include "pkb/stores/relationships/types/UsesPStore.h"

/**
 * Unit tests for the UsesPStore class.
 *
 * Tests the functionality of managing "Uses" relationships for procedures,
 * focusing on the ability to track which variables are used by which procedures.
 * The UsesPStore class is responsible for recording and querying these relationships,
 * ensuring accurate and efficient access to the data.
 */
TEST_CASE("UsesPStore Functionality") {
    // Initialize UsesPStore instance for testing.
    UsesPStore usesPStore;

    // Test adding "Uses" relationships and verifying their existence.
    SECTION("Add and Check Uses Relationships for Procedures") {
        // Add "Uses" relationships between procedures and variables.
        usesPStore.addRelationship("main", "x");
        usesPStore.addRelationship("main", "y");
        usesPStore.addRelationship("computeCentroid", "z");

        // Verify that the added relationships are correctly identified.
        REQUIRE(usesPStore.hasRelationship("main", "x")); // "main" procedure uses variable "x".
        REQUIRE(usesPStore.hasRelationship("main", "y")); // "main" procedure uses variable "y".
        REQUIRE(usesPStore.hasRelationship("computeCentroid", "z")); // "computeCentroid" uses variable "z".

        // Ensure that a non-existent relationship returns false.
        REQUIRE_FALSE(usesPStore.hasRelationship("main", "z")); // "main" does not use variable "z".
    }

        // Test retrieving procedures that use a specific variable.
    SECTION("Retrieve Procedures Using a Specific Variable") {
        // Add "Uses" relationships between procedures and variables.
        usesPStore.addRelationship("main", "x");
        usesPStore.addRelationship("computeCentroid", "x");

        // Verify retrieval of all procedures that use the variable "x".
        auto proceduresUsingX = usesPStore.getRelationshipsByValue("x");
        auto expectedProcedures = std::unordered_set<std::string>{"main", "computeCentroid"};

        REQUIRE(proceduresUsingX == expectedProcedures); // Both "main" and "computeCentroid" use "x".
    }

        // Test retrieving variables used by a specific procedure.
    SECTION("Retrieve Variables Used by a Procedure") {
        // Add "Uses" relationships for a single procedure.
        usesPStore.addRelationship("main", "x");
        usesPStore.addRelationship("main", "y");

        // Verify retrieval of all variables used by the "main" procedure.
        auto variablesUsedByMain = usesPStore.getRelationshipsByKey("main");
        auto expectedVariables = std::unordered_set<std::string>{"x", "y"};

        REQUIRE(variablesUsedByMain == expectedVariables); // "main" uses variables "x" and "y".
    }

        // Test the ability to clear all "Uses" relationships from the store.
    SECTION("Clear All Uses Relationships") {
        // Initially, the store should be empty.
        REQUIRE(usesPStore.isEmpty());

        // Adding a relationship should change the store's state to non-empty.
        usesPStore.addRelationship("main", "x");
        REQUIRE_FALSE(usesPStore.isEmpty());

        // Clearing the store should reset its state to empty.
        usesPStore.clear();
        REQUIRE(usesPStore.isEmpty());
    }
}
