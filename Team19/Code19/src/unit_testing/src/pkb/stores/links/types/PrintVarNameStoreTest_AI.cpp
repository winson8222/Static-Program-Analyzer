#include "catch.hpp"
#include "pkb/stores/links/types/PrintVarNameStore.h"

TEST_CASE("pkb/stores/links/types/PrintVarNameStore") {
    SECTION("PrintVarNameStore can be created") {
        PrintVarNameStore printVarNameStore;
    }

    SECTION("PrintVarNameStore can add links") {
        PrintVarNameStore printVarNameStore;
        printVarNameStore.addLink(1, "one");
        printVarNameStore.addLink(2, "two");
        printVarNameStore.addLink(3, "three");
        REQUIRE(printVarNameStore.hasLink(1, "one"));
        REQUIRE(printVarNameStore.hasLink(2, "two"));
        REQUIRE(printVarNameStore.hasLink(3, "three"));
    }

    SECTION("PrintVarNameStore can get linkers") {
        PrintVarNameStore printVarNameStore;
        printVarNameStore.addLink(1, "foo");
        printVarNameStore.addLink(2, "foo");
        printVarNameStore.addLink(3, "foo");
        REQUIRE(printVarNameStore.getLinker("foo") == std::unordered_set<int>({1, 2, 3}));
    }

    SECTION("PrintVarNameStore can get linked") {
        PrintVarNameStore printVarNameStore;
        printVarNameStore.addLink(1, "foo");
        printVarNameStore.addLink(2, "foo");
        printVarNameStore.addLink(3, "foo");
        REQUIRE(printVarNameStore.getLinked(1) == "foo");
        REQUIRE(printVarNameStore.getLinked(2) == "foo");
        REQUIRE(printVarNameStore.getLinked(3) == "foo");
    }

    SECTION("PrintVarNameStore can check if link exists") {
        PrintVarNameStore printVarNameStore;
        printVarNameStore.addLink(1, "foo");
        REQUIRE(printVarNameStore.hasLink(1, "foo"));
    }
}
