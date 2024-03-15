#include "catch.hpp"
#include "pkb/stores/links/types/ReadVarNameStore.h"

TEST_CASE("pkb/stores/links/types/ReadVarNameStore") {
    SECTION("ReadVarNameStore can be created") {
        ReadVarNameStore readVarNameStore;
    }

    SECTION("ReadVarNameStore can add links") {
        ReadVarNameStore readVarNameStore;
        readVarNameStore.addLink(1, "one");
        readVarNameStore.addLink(2, "two");
        readVarNameStore.addLink(3, "three");
        REQUIRE(readVarNameStore.hasLink(1, "one"));
        REQUIRE(readVarNameStore.hasLink(2, "two"));
        REQUIRE(readVarNameStore.hasLink(3, "three"));
    }

    SECTION("ReadVarNameStore can get linkers") {
        ReadVarNameStore readVarNameStore;
        readVarNameStore.addLink(1, "foo");
        readVarNameStore.addLink(2, "foo");
        readVarNameStore.addLink(3, "foo");
        REQUIRE(readVarNameStore.getLinker("foo") == std::unordered_set<int>({1, 2, 3}));
    }

    SECTION("ReadVarNameStore can get linked") {
        ReadVarNameStore readVarNameStore;
        readVarNameStore.addLink(1, "foo");
        readVarNameStore.addLink(2, "foo");
        readVarNameStore.addLink(3, "foo");
        REQUIRE(readVarNameStore.getLinked(1) == "foo");
        REQUIRE(readVarNameStore.getLinked(2) == "foo");
        REQUIRE(readVarNameStore.getLinked(3) == "foo");
    }

    SECTION("ReadVarNameStore can check if link exists") {
        ReadVarNameStore readVarNameStore;
        readVarNameStore.addLink(1, "foo");
        REQUIRE(readVarNameStore.hasLink(1, "foo"));
    }

    SECTION("getLinked ReadVarNameStore when empty") {
        ReadVarNameStore readVarNameStore;
        REQUIRE_THROWS(readVarNameStore.getLinked(1));
    }
}
