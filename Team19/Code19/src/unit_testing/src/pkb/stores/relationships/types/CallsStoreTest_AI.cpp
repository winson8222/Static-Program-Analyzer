#include "catch.hpp"
#include "pkb/stores/relationships/types/CallsStore.h"

TEST_CASE("pkb/stores/relationships/types/CallsStore") {
    auto callsStore = std::make_shared<CallsStore>();

    SECTION("isEmpty: Initially Empty") {
        REQUIRE(callsStore->isEmpty());
    }

    SECTION("Add and Check Relationship") {
        callsStore->addRelationship("Main", "Helper");
        REQUIRE_FALSE(callsStore->isEmpty());
        REQUIRE(callsStore->hasRelationship("Main", "Helper"));
    }

    SECTION("Retrieve Calls Relationships") {
        callsStore->addRelationship("Main", "Helper");
        callsStore->addRelationship("Main", "Logger");
        auto calledProcedures = callsStore->getRelationshipsByKey("Main");
        REQUIRE(calledProcedures.size() == 2);
        REQUIRE(calledProcedures.find("Helper") != calledProcedures.end());
        REQUIRE(calledProcedures.find("Logger") != calledProcedures.end());
    }

    SECTION("Retrieve Callers") {
        callsStore->addRelationship("Main", "Helper");
        callsStore->addRelationship("UI", "Helper");
        auto callers = callsStore->getRelationshipsByValue("Helper");
        REQUIRE(callers.size() == 2);
        REQUIRE(callers.find("Main") != callers.end());
        REQUIRE(callers.find("UI") != callers.end());
    }

    SECTION("Check Non-existent Relationship") {
        REQUIRE_FALSE(callsStore->hasRelationship("Main", "NonExistent"));
    }

    SECTION("Get All Procedures With Calls") {
        callsStore->addRelationship("Main", "Helper");
        callsStore->addRelationship("UI", "Logger");
        auto allCallers = callsStore->getKeys();
        auto allCallees = callsStore->getValues();
        REQUIRE(allCallers.size() == 2);
        REQUIRE(allCallees.size() == 2);
    }

    SECTION("Clear Store") {
        callsStore->addRelationship("Main", "Helper");
        REQUIRE_FALSE(callsStore->isEmpty());
        callsStore->clear();
        REQUIRE(callsStore->isEmpty());
    }
}
