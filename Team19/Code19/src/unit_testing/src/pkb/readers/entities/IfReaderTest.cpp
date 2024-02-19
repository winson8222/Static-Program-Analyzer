#include "catch.hpp"
#include "pkb/PKBManager.h"

TEST_CASE("IfReader: Basic Functionality") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto pkbReader = pkbManager->getPKBReaderManager();
    auto pkbWriter = pkbManager->getPKBWriterManager();
    auto ifReader = pkbReader->getIfReader();
    auto ifWriter = pkbWriter->getIfWriter();

    SECTION("getAllIfs: Empty") {
        REQUIRE(ifReader->getAllIfs().empty());
    }

    SECTION("getAllIfs: Non-empty") {
        ifWriter->insertIf(7);
        ifWriter->insertIf(8);
        REQUIRE(ifReader->getAllIfs() == std::unordered_set<int>{7, 8});
        ifWriter->clear();
    }
}
