#include "catch.hpp"
#include "pkb/PKBManager.h"
#include "pkb/stores/relationships/types/CallsTStore.h"
#include "pkb/readers/relationships/CallsTReader.h"

TEST_CASE("pkb/readers/relationships/CallsTReader") {
    auto callsTStore = std::make_shared<CallsTStore>();
    CallsTReader callsTReader(callsTStore);

    SECTION("isEmpty: Empty on initialization") {
        REQUIRE(callsTReader.isEmpty());
    }

    // Assume these methods exist to add transitive calls relationships directly to the store for testing
    callsTStore->addRelationship("Main", "Sub1");
    callsTStore->addRelationship("Sub1", "Sub2");
    // Simulate transitive relationship (Main indirectly calls Sub2 through Sub1)
    callsTStore->addRelationship("Main", "Sub2");

    SECTION("isEmpty: Not empty after adding relationships") {
        REQUIRE_FALSE(callsTReader.isEmpty());
    }

    SECTION("hasRelationship: Direct and Transitive Calls") {
        REQUIRE(callsTReader.hasRelationship("Main", "Sub1")); // Direct call
        REQUIRE(callsTReader.hasRelationship("Main", "Sub2")); // Transitive call
        REQUIRE_FALSE(callsTReader.hasRelationship("Sub2", "Main")); // Not in calls relationship
    }

    SECTION("getTransitivelyCalledProcedures") {
        auto calledProcedures = callsTReader.getTransitivelyCalledProcedures("Main");
        REQUIRE(calledProcedures.size() == 2);
        REQUIRE(calledProcedures.find("Sub1") != calledProcedures.end());
        REQUIRE(calledProcedures.find("Sub2") != calledProcedures.end());
    }

    SECTION("getTransitiveCallersOfProcedure") {
        auto callers = callsTReader.getTransitiveCallersOfProcedure("Sub2");
        REQUIRE(callers.size() == 2);
        REQUIRE(callers.find("Main") != callers.end());
    }

    SECTION("getAllTransitiveCallers") {
        auto allCallers = callsTReader.getAllTransitiveCallers();
        REQUIRE(allCallers.size() == 2);
        REQUIRE(allCallers.find("Main") != allCallers.end());
    }

    SECTION("getAllTransitiveCallees") {
        auto allCallees = callsTReader.getAllTransitiveCallees();
        REQUIRE(allCallees.size() == 2);
        REQUIRE(allCallees.find("Sub1") != allCallees.end());
        REQUIRE(allCallees.find("Sub2") != allCallees.end());
    }

    SECTION("hasAnyTransitiveCalls") {
        REQUIRE(callsTReader.hasAnyTransitiveCalls("Main"));
        REQUIRE_FALSE(callsTReader.hasAnyTransitiveCalls("Sub2")); // "Sub2" does not call anyone, even transitively
    }

    SECTION("isTransitiveCallee") {
        REQUIRE(callsTReader.isTransitiveCallee("Sub2"));
        REQUIRE_FALSE(callsTReader.isTransitiveCallee("Main")); // "Main" is not called, even transitively
    }
}
