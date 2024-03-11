#include "catch.hpp"
#include "pkb/stores/relationships/types/CallsTStore.h"

TEST_CASE("pkb/stores/relationships/types/CallsTStore") {
    auto callsTStore = std::make_shared<CallsTStore>();

    SECTION("isEmpty: Initially Empty") {
        REQUIRE(callsTStore->isEmpty());
    }

    SECTION("Add Direct Calls Relationship") {
        callsTStore->addRelationship("Main", "Helper");
        REQUIRE_FALSE(callsTStore->isEmpty());
        REQUIRE(callsTStore->hasRelationship("Main", "Helper"));
    }

    SECTION("Add Transitive Calls Relationship") {
        callsTStore->addRelationship("Main", "Helper");
        callsTStore->addRelationship("Helper", "Logger");
        callsTStore->addRelationship("Main", "Logger");
        REQUIRE(callsTStore->hasRelationship("Main", "Logger"));
    }

    SECTION("Retrieve Transitively Called Procedures") {
        callsTStore->addRelationship("Main", "Helper");
        callsTStore->addRelationship("Helper", "Logger");
        callsTStore->addRelationship("Main", "Logger");
        auto transitivelyCalled = callsTStore->getRelationshipsByKey("Main");
        REQUIRE(transitivelyCalled.size() >= 2);
        REQUIRE(transitivelyCalled.find("Helper") != transitivelyCalled.end());
        REQUIRE(transitivelyCalled.find("Logger") != transitivelyCalled.end());
    }

    SECTION("Retrieve Transitive Callers") {
        callsTStore->addRelationship("Main", "Helper");
        callsTStore->addRelationship("Helper", "Logger");
        callsTStore->addRelationship("Main", "Logger");
        auto transitiveCallers = callsTStore->getRelationshipsByValue("Logger");
        REQUIRE(transitiveCallers.find("Main") != transitiveCallers.end());
        REQUIRE(transitiveCallers.find("Helper") != transitiveCallers.end());
    }

    SECTION("Check Non-existent Transitive Relationship") {
        REQUIRE_FALSE(callsTStore->hasRelationship("Main", "NonExistent"));
    }

    SECTION("Get All Procedures Involved in Transitive Calls") {
        callsTStore->addRelationship("Main", "Helper");
        callsTStore->addRelationship("UI", "Logger");
        auto allTransitiveCallers = callsTStore->getKeys();
        auto allTransitiveCallees = callsTStore->getValues();
        REQUIRE(allTransitiveCallers.size() >= 2);
        REQUIRE(allTransitiveCallees.size() >= 2);
    }

    SECTION("Clear Store") {
        callsTStore->addRelationship("Main", "Helper");
        REQUIRE_FALSE(callsTStore->isEmpty());
        callsTStore->clear();
        REQUIRE(callsTStore->isEmpty());
    }
}
