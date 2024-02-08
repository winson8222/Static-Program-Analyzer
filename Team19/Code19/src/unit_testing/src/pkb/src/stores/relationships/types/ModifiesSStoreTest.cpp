#include "catch.hpp"
#include "pkb/stores/relationships/types/ModifiesSStore.h"

/**
 * Unit tests for the ModifiesSStore class.
 *
 * Tests the functionality of managing "Modifies" relationships for statements,
 * focusing on the ability to track which variables are modified by which statements.
 * The ModifiesSStore class is responsible for recording and querying these relationships
 * between statement numbers and the variables they modify, ensuring accurate and
 * efficient access to the data.
 */
TEST_CASE("ModifiesSStore Functionality") {
    // Initialize ModifiesSStore instance for testing.
    ModifiesSStore modifiesSStore;

    // Test adding "Modifies" relationships and verifying their existence.
    SECTION("Add and Check Modifies Relationships for Statements") {
        // Add "Modifies" relationships between statements and variables.
        modifiesSStore.addRelationship(1, "x");
        modifiesSStore.addRelationship(2, "y");
        modifiesSStore.addRelationship(3, "z");

        // Verify that the added relationships are correctly identified.
        REQUIRE(modifiesSStore.hasRelationship(1, "x")); // Statement 1 modifies variable "x".
        REQUIRE(modifiesSStore.hasRelationship(2, "y")); // Statement 2 modifies variable "y".
        REQUIRE(modifiesSStore.hasRelationship(3, "z")); // Statement 3 modifies variable "z".

        // Ensure that a non-existent relationship returns false.
        REQUIRE_FALSE(modifiesSStore.hasRelationship(1, "z")); // Statement 1 does not modify variable "z".
    }

        // Test retrieving statements that modify a specific variable.
    SECTION("Retrieve Statements Modifying a Specific Variable") {
        // Add "Modifies" relationships between statements and variables.
        modifiesSStore.addRelationship(1, "x");
        modifiesSStore.addRelationship(4, "x");

        // Verify retrieval of all statements that modify the variable "x".
        auto statementsModifyingX = modifiesSStore.getRelationshipsByValue("x");
        auto expectedStatements = unordered_set<int>{1, 4};

        REQUIRE(statementsModifyingX == expectedStatements); // Statements 1 and 4 modify "x".
    }

        // Test retrieving variables modified by a specific statement.
    SECTION("Retrieve Variables Modified by a Statement") {
        // Add "Modifies" relationships for a single statement.
        modifiesSStore.addRelationship(1, "x");
        modifiesSStore.addRelationship(1, "y");

        // Verify retrieval of all variables modified by Statement 1.
        auto variablesModifiedByStmt1 = modifiesSStore.getRelationshipsByKey(1);
        auto expectedVariables = unordered_set<std::string>{"x", "y"};

        REQUIRE(variablesModifiedByStmt1 == expectedVariables); // Statement 1 modifies variables "x" and "y".
    }

        // Test the ability to clear all "Modifies" relationships from the store.
    SECTION("Clear All Modifies Relationships") {
        // Initially, the store should be empty.
        REQUIRE(modifiesSStore.isEmpty());

        // Adding a relationship should change the store's state to non-empty.
        modifiesSStore.addRelationship(1, "x");
        REQUIRE_FALSE(modifiesSStore.isEmpty());

        // Clearing the store should reset its state to empty.
        modifiesSStore.clear();
        REQUIRE(modifiesSStore.isEmpty());
    }
}
