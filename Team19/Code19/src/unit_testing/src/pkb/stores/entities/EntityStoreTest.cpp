#include "catch.hpp"

#include "pkb/stores/entities/EntityStore.h"

using namespace std;

TEST_CASE("pkb/stores/entities/EntityStore") {
    SECTION("addEntity: Basic Int") {
        EntityStore<int> entityStore;
        entityStore.addEntity(1);
        entityStore.addEntity(2);
        entityStore.addEntity(3);
        auto expected = unordered_set<int>{1, 2, 3};
        REQUIRE(entityStore.getAllEntities() == expected);
    }

    SECTION("addEntity: Duplicate Int") {
        EntityStore<int> entityStore;
        entityStore.addEntity(1);
        entityStore.addEntity(1);
        entityStore.addEntity(1);
        auto expected = unordered_set<int>{1};
        REQUIRE(entityStore.getAllEntities() == expected);
    }

    SECTION("addEntity: Basic String") {
        EntityStore<string> entityStore;
        entityStore.addEntity("a");
        entityStore.addEntity("b");
        entityStore.addEntity("c");
        auto expected = unordered_set<string>{"a", "b", "c"};
        REQUIRE(entityStore.getAllEntities() == expected);
    }

    SECTION("addEntity: Duplicate String") {
        EntityStore<string> entityStore;
        entityStore.addEntity("a");
        entityStore.addEntity("a");
        entityStore.addEntity("a");
        auto expected = unordered_set<string>{"a"};
        REQUIRE(entityStore.getAllEntities() == expected);
    }

    SECTION("clear: Empty Store") {
        EntityStore<int> entityStore;
        entityStore.clear();
        REQUIRE(entityStore.getAllEntities().empty());
    }

    SECTION("clear: Non-Empty Store") {
        EntityStore<int> entityStore;
        entityStore.addEntity(1);
        entityStore.addEntity(2);
        entityStore.addEntity(3);
        entityStore.clear();
        REQUIRE(entityStore.getAllEntities().empty());
    }
}
