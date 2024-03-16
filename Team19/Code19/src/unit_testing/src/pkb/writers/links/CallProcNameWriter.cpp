#include "catch.hpp"

#include "pkb/stores/links/types/CallProcNameStore.h"
#include "pkb/writers/links/CallProcNameWriter.h"

TEST_CASE("pkb/writers/links/CallProcNameWriter") {
    SECTION("CallProcNameWriter can be created") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameWriter callProcNameWriter(callProcNameStore);
    }

    SECTION("CallProcNameWriter can add call proc name") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameWriter callProcNameWriter(callProcNameStore);
        callProcNameWriter.addCallProcName(1, "foo");
        REQUIRE(callProcNameStore->getLinker("foo") == std::unordered_set<int>({1}));
    }

    SECTION("CallProcNameWriter can add link") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameWriter callProcNameWriter(callProcNameStore);
        callProcNameWriter.addLink(1, "foo");
        REQUIRE(callProcNameStore->getLinker("foo") == std::unordered_set<int>({1}));
    }

    SECTION("CallProcNameWriter can clear") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameWriter callProcNameWriter(callProcNameStore);
        callProcNameStore->addLink(1, "foo");
        callProcNameWriter.clear();
        REQUIRE(callProcNameStore->getLinker("foo").empty());
    }
}
