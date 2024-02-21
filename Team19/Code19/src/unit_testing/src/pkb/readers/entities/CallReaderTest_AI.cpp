#include "catch.hpp"
#include "pkb/PKBManager.h"

TEST_CASE("CallReader: Basic Functionality") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto pkbReader = pkbManager->getPKBReaderManager();
    auto pkbWriter = pkbManager->getPKBWriterManager();
    auto callReader = pkbReader->getCallReader();
    auto callWriter = pkbWriter->getCallWriter();

    SECTION("getAllCalls: Empty") {
        REQUIRE(callReader->getAllCalls().empty());
    }

    SECTION("getAllCalls: Non-empty") {
        callWriter->insertCall(3);
        callWriter->insertCall(4);
        REQUIRE(callReader->getAllCalls() == std::unordered_set<int>{3, 4});
        callWriter->clear();
    }
}
