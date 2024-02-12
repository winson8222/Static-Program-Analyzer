#include "catch.hpp"
#include "pkb/stores/relationships/RelationshipStore.h"

TEST_CASE("pkb/stores/relationships/RelationshipStore") {
    SECTION("hasRelationship: Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        REQUIRE_FALSE(relationshipStore.hasRelationship(1, 2));
    }

    SECTION("hasRelationship: Non-Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        REQUIRE(relationshipStore.hasRelationship(1, 2));
    }

    SECTION("hasRelationship: Non-Existent Relationship") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        REQUIRE_FALSE(relationshipStore.hasRelationship(2, 1));
    }

    SECTION("isEmpty: Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        REQUIRE(relationshipStore.isEmpty());
    }

    SECTION("isEmpty: Non-Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        REQUIRE_FALSE(relationshipStore.isEmpty());
    }

    SECTION("addRelationship: Basic") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        auto expected = std::unordered_map<int, std::unordered_set<int>>{{1, {2}}};
        REQUIRE(relationshipStore.getKeyValueRelationships() == expected);
    }

    SECTION("addRelationship: Duplicate") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        relationshipStore.addRelationship(1, 2);
        auto expected = std::unordered_map<int, std::unordered_set<int>>{{1, {2}}};
        REQUIRE(relationshipStore.getKeyValueRelationships() == expected);
    }

    SECTION("clear: Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.clear();
        REQUIRE(relationshipStore.isEmpty());
    }

    SECTION("clear: Non-Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        relationshipStore.addRelationship(2, 3);
        relationshipStore.clear();
        REQUIRE(relationshipStore.isEmpty());
    }

    SECTION("getKeyValueRelationships: Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        auto expected = std::unordered_map<int, std::unordered_set<int>>{};
        REQUIRE(relationshipStore.getKeyValueRelationships() == expected);
    }

    SECTION("getKeyValueRelationships: Non-Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        relationshipStore.addRelationship(1, 3);
        relationshipStore.addRelationship(2, 3);
        auto expected = std::unordered_map<int, std::unordered_set<int>>{
                {1, {2, 3}},
                {2, {3}}
        };
        REQUIRE(relationshipStore.getKeyValueRelationships() == expected);
    }

    SECTION("getValueKeyRelationships: Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        auto expected = std::unordered_map<int, std::unordered_set<int>>{};
        REQUIRE(relationshipStore.getValueKeyRelationships() == expected);
    }

    SECTION("getValueKeyRelationships: Non-Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        relationshipStore.addRelationship(1, 3);
        relationshipStore.addRelationship(2, 3);
        auto expected = std::unordered_map<int, std::unordered_set<int>>{
                {2, {1}},
                {3, {1, 2}}
        };
        REQUIRE(relationshipStore.getValueKeyRelationships() == expected);
    }

    SECTION("getRelationshipsByKey: Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        auto expected = std::unordered_set<int>{};
        REQUIRE(relationshipStore.getRelationshipsByKey(1) == expected);
    }

    SECTION("getRelationshipsByKey: Non-Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        relationshipStore.addRelationship(1, 3);
        relationshipStore.addRelationship(2, 3);
        auto expected = std::unordered_set<int>{2, 3};
        REQUIRE(relationshipStore.getRelationshipsByKey(1) == expected);
    }

    SECTION("getRelationshipsByValue: Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        auto expected = std::unordered_set<int>{};
        REQUIRE(relationshipStore.getRelationshipsByValue(1) == expected);
    }

    SECTION("getRelationshipsByValue: Non-Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        relationshipStore.addRelationship(1, 3);
        relationshipStore.addRelationship(2, 3);
        auto expected = std::unordered_set<int>{1};
        REQUIRE(relationshipStore.getRelationshipsByValue(2) == expected);
        expected = std::unordered_set<int>{1, 2};
        REQUIRE(relationshipStore.getRelationshipsByValue(3) == expected);
    }

  SECTION("getKeys: Empty Store") {
    RelationshipStore<int, int> relationshipStore;
    auto expected = std::unordered_set<int>{};
    REQUIRE(relationshipStore.getKeys() == expected);
  }

    SECTION("getKeys: Non-Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        relationshipStore.addRelationship(1, 3);
        relationshipStore.addRelationship(2, 3);
        auto expected = std::unordered_set<int>{1, 2};
        REQUIRE(relationshipStore.getKeys() == expected);
    }

    SECTION("getValues: Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        auto expected = std::unordered_set<int>{};
        REQUIRE(relationshipStore.getValues() == expected);
    }

    SECTION("getValues: Non-Empty Store") {
        RelationshipStore<int, int> relationshipStore;
        relationshipStore.addRelationship(1, 2);
        relationshipStore.addRelationship(1, 3);
        relationshipStore.addRelationship(2, 3);
        auto expected = std::unordered_set<int>{2, 3};
        REQUIRE(relationshipStore.getValues() == expected);
    }
}