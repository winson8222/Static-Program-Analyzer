#include "catch.hpp"
#include "pkb/stores/links/LinkStore.h"

TEST_CASE("pkb/stores/links/LinkStore") {
    SECTION("int to string") {
        LinkStore<int, std::string> linkStore;
        SECTION("addLink and hasLink: Basic") {
            linkStore.addLink(1, "one");
            linkStore.addLink(2, "two");
            linkStore.addLink(3, "three");
            REQUIRE(linkStore.hasLink(1, "one"));
            REQUIRE(linkStore.hasLink(2, "two"));
            REQUIRE(linkStore.hasLink(3, "three"));
        }

        SECTION("addLink, hasLink, getLinker, getLinked: Multiple Linkers") {
            linkStore.addLink(1, "foo");
            linkStore.addLink(2, "foo");
            linkStore.addLink(3, "foo");
            REQUIRE(linkStore.hasLink(1, "foo"));
            REQUIRE(linkStore.hasLink(2, "foo"));
            REQUIRE(linkStore.hasLink(3, "foo"));
            REQUIRE(linkStore.getLinker("foo") == std::unordered_set<int>({1, 2, 3}));
            REQUIRE(linkStore.getLinked(1) == "foo");
            REQUIRE(linkStore.getLinked(2) == "foo");
            REQUIRE(linkStore.getLinked(3) == "foo");
        }

        SECTION("getLinker and getLinked: Non-existent") {
            REQUIRE(linkStore.getLinker("non-existent").empty());
            REQUIRE(linkStore.getLinked(1).empty());
        }
    }

    SECTION("int to int") {
        LinkStore<int, int> linkStore;

        SECTION("getLinker and getLinked: Non-existent") {
            REQUIRE(linkStore.getLinker(1).empty());
            REQUIRE(linkStore.getLinked(1) == 0);
        }
    }
}