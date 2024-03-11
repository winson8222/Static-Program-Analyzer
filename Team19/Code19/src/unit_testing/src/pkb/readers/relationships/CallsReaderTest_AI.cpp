#include "catch.hpp"
#include "pkb/PKBManager.h"
#include "pkb/stores/relationships/types/CallsStore.h"
#include "pkb/readers/relationships/CallsReader.h"

TEST_CASE("pkb/readers/relationships/CallsReader") {
    auto callsStore = std::make_shared<CallsStore>();
    CallsReader callsReader(callsStore);

    SECTION("isEmpty: Empty on initialization") {
        REQUIRE(callsReader.isEmpty());
    }

    // Assume these methods exist to add calls relationships directly to the store for testing
    callsStore->addRelationship("Main", "Sub1");
    callsStore->addRelationship("Sub1", "Sub2");

    SECTION("isEmpty: Not empty after adding relationships") {
        REQUIRE_FALSE(callsReader.isEmpty());
    }

    SECTION("hasRelationship") {
        REQUIRE(callsReader.hasRelationship("Main", "Sub1"));
        REQUIRE(callsReader.hasRelationship("Sub1", "Sub2"));
        REQUIRE_FALSE(callsReader.hasRelationship("Main", "Sub2")); // Not directly calls
    }

    SECTION("getDirectlyCalledProcedures") {
        auto directlyCalledProcedures = callsReader.getDirectlyCalledProcedures("Main");
        REQUIRE(directlyCalledProcedures == std::unordered_set<std::string>{"Sub1"});
    }

    SECTION("getDirectCallersOfProcedure") {
        auto directCallers = callsReader.getDirectCallersOfProcedure("Sub2");
        REQUIRE(directCallers == std::unordered_set<std::string>{"Sub1"});
    }

    SECTION("getAllDirectCallers") {
        auto allDirectCallers = callsReader.getAllDirectCallers();
        REQUIRE(allDirectCallers.size() == 2);
        REQUIRE(allDirectCallers.find("Main") != allDirectCallers.end());
        REQUIRE(allDirectCallers.find("Sub1") != allDirectCallers.end());
    }

    SECTION("getAllDirectCallees") {
        auto allDirectCallees = callsReader.getAllDirectCallees();
        REQUIRE(allDirectCallees.size() == 2);
        REQUIRE(allDirectCallees.find("Sub1") != allDirectCallees.end());
        REQUIRE(allDirectCallees.find("Sub2") != allDirectCallees.end());
    }

    SECTION("hasAnyDirectCalls") {
        REQUIRE(callsReader.hasAnyDirectCalls("Main"));
        REQUIRE_FALSE(callsReader.hasAnyDirectCalls("Sub2")); // "Sub2" does not call anyone
    }

    SECTION("isDirectCallee") {
        REQUIRE(callsReader.isDirectCallee("Sub2"));
        REQUIRE_FALSE(callsReader.isDirectCallee("Main")); // "Main" is not called directly by any procedure
    }
}
