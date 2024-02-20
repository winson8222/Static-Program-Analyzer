#include "catch.hpp"
#include "pkb/PKBManager.h"

TEST_CASE("PrintReader: Basic Functionality") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto printReader = pkbManager->getPKBReaderManager()->getPrintReader();
    auto printWriter = pkbManager->getPKBWriterManager()->getPrintWriter();

    SECTION("getAllPrints: Empty") {
        REQUIRE(printReader->getAllPrints().empty());
    }

    SECTION("getAllPrints: Non-empty") {
        printWriter->insertPrint(1);
        printWriter->insertPrint(2);
        REQUIRE(printReader->getAllPrints() == std::unordered_set<int>{1, 2});
        printWriter->clear();
    }
}
