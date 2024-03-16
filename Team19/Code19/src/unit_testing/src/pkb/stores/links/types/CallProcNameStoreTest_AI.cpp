#include "catch.hpp"
#include "pkb/stores/links/types/CallProcNameStore.h"

TEST_CASE("pkb/stores/links/types/CallProcNameStore") {
    SECTION("CallProcNameStore can be created") {
        CallProcNameStore callProcNameStore;
    }

    SECTION("CallProcNameStore can add links") {
        CallProcNameStore callProcNameStore;
        callProcNameStore.addLink(1, "one");
        callProcNameStore.addLink(2, "two");
        callProcNameStore.addLink(3, "three");
        REQUIRE(callProcNameStore.hasLink(1, "one"));
        REQUIRE(callProcNameStore.hasLink(2, "two"));
        REQUIRE(callProcNameStore.hasLink(3, "three"));
    }

    SECTION("CallProcNameStore can get linkers") {
        CallProcNameStore callProcNameStore;
        callProcNameStore.addLink(1, "foo");
        callProcNameStore.addLink(2, "foo");
        callProcNameStore.addLink(3, "foo");
        REQUIRE(callProcNameStore.getLinker("foo") == std::unordered_set<int>({1, 2, 3}));
    }

    SECTION("CallProcNameStore can get linked") {
        CallProcNameStore callProcNameStore;
        callProcNameStore.addLink(1, "foo");
        callProcNameStore.addLink(2, "foo");
        callProcNameStore.addLink(3, "foo");
        REQUIRE(callProcNameStore.getLinked(1) == "foo");
        REQUIRE(callProcNameStore.getLinked(2) == "foo");
        REQUIRE(callProcNameStore.getLinked(3) == "foo");
    }

    SECTION("CallProcNameStore can check if link exists") {
        CallProcNameStore callProcNameStore;
        callProcNameStore.addLink(1, "foo");
        REQUIRE(callProcNameStore.hasLink(1, "foo"));
    }
}
