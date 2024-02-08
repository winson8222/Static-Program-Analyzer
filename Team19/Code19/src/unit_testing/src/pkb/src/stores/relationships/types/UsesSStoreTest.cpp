#include "catch.hpp"
#include "pkb/stores/relationships/types/UsesSStore.h"

/**
 * Unit tests for the UsesSStore class.
 *
 * Tests the functionality of managing "Uses" relationships for statements,
 * focusing on the ability to track which variables are used by which statements.
 * The UsesSStore class is responsible for recording and querying these relationships
 * between statement numbers and the variables they use, ensuring accurate and
 * efficient access to the data.
 */
TEST_CASE("UsesSStore Functionality") {
    // Initialize UsesSStore instance for testing.
    UsesSStore usesSStore;

    // Test adding "Uses" relationships and verifying their existence.
    SECTION("Add and Check Uses Relationships for Statements") {
        // Add "Uses" relationships between statements and variables.
        usesSStore.addRelationship(1, "x");
        usesSStore.addRelationship(2, "y");
        usesSStore.addRelationship(3, "z");

        // Verify that the added relationships are correctly identified.
        REQUIRE(usesSStore.hasRelationship(1, "x")); // Statement 1 uses variable "x".
        REQUIRE(usesSStore.hasRelationship(2, "y")); // Statement 2 uses variable "y".
        REQUIRE(usesSStore.hasRelationship(3, "z")); // Statement 3 uses variable "z".

        // Ensure that a non-existent relationship returns false.
        REQUIRE_FALSE(usesSStore.hasRelationship(1, "y")); // Statement 1 does not use variable "y".
    }

        // Test retrieving statements that use a specific variable.
    SECTION("Retrieve Statements Using a Specific Variable") {
        // Add "Uses" relationships between statements and variables.
        usesSStore.addRelationship(1, "x");
        usesSStore.addRelationship(4, "x");

        // Verify retrieval of all statements that use the variable "x".
        auto statementsUsingX = usesSStore.getRelationshipsByValue("x");
        auto expectedStatements = unordered_set<int>{1, 4};

        REQUIRE(statementsUsingX == expectedStatements); // Statements 1 and 4 use "x".
    }

        // Test retrieving variables used by a specific statement.
    SECTION("Retrieve Variables Used by a Statement") {
        // Add "Uses" relationships for a single statement.
        usesSStore.addRelationship(1, "x");
        usesSStore.addRelationship(1, "y");

        // Verify retrieval of all variables used by Statement 1.
        auto variablesUsedByStmt1 = usesSStore.getRelationshipsByKey(1);
        auto expectedVariables = unordered_set<std::string>{"x", "y"};

        REQUIRE(variablesUsedByStmt1 == expectedVariables); // Statement 1 uses variables "x" and "y".
    }

        // Test the ability to clear all "Uses" relationships from the store.
    SECTION("Clear All Uses Relationships") {
        // Initially, the store should be empty.
        REQUIRE(usesSStore.isEmpty());

        // Adding a relationship should change the store's state to non-empty.
        usesSStore.addRelationship(1, "x");
        REQUIRE_FALSE(usesSStore.isEmpty());

        // Clearing the store should reset its state to empty.
        usesSStore.clear();
        REQUIRE(usesSStore.isEmpty());
    }
}
