#include "catch.hpp"

#include "pkb/stores/links/types/CallProcNameStore.h"
#include "pkb/readers/links/CallProcNameReader.h"

TEST_CASE("pkb/readers/links/CallProcNameReader") {
    SECTION("CallProcNameReader can be created") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameReader callProcNameReader(callProcNameStore);
    }

    SECTION("CallProcNameReader can get callers") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameReader callProcNameReader(callProcNameStore);
        callProcNameStore->addLink(1, "foo");
        callProcNameStore->addLink(2, "foo");
        callProcNameStore->addLink(3, "foo");
        REQUIRE(callProcNameReader.getCallers("foo") == std::unordered_set<int>({1, 2, 3}));
    }

    SECTION("CallProcNameReader can get called procedure name") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameReader callProcNameReader(callProcNameStore);
        callProcNameStore->addLink(1, "foo");
        REQUIRE(callProcNameReader.getCalledProcedureName(1) == "foo");
    }

    SECTION("CallProcNameReader can check if a statement calls a procedure") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameReader callProcNameReader(callProcNameStore);
        callProcNameStore->addLink(1, "foo");
        REQUIRE(callProcNameReader.isCalled(1, "foo"));
    }

    SECTION("CallProcNameReader can check if it is empty") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameReader callProcNameReader(callProcNameStore);
        REQUIRE(callProcNameReader.isEmpty());
    }

    SECTION("CallProcNameReader can check if doesn't exist") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameReader callProcNameReader(callProcNameStore);
        REQUIRE_FALSE(callProcNameReader.isCalled(1, "foo"));
    }

    SECTION("getCalledProcedureName returns empty set if statement does not call any procedure") {
        std::shared_ptr<CallProcNameStore> callProcNameStore = std::make_shared<CallProcNameStore>();
        CallProcNameReader callProcNameReader(callProcNameStore);
        REQUIRE_THROWS(callProcNameReader.getCalledProcedureName(1));
    }
}
