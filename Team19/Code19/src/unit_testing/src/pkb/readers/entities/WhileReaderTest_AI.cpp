#include "catch.hpp"
#include "pkb/PKBManager.h"

TEST_CASE("WhileReader: Basic Functionality") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto whileReader = pkbManager->getPKBReaderManager()->getWhileReader();
    auto whileWriter = pkbManager->getPKBWriterManager()->getWhileWriter();

    SECTION("getAllWhiles: Empty") {
        REQUIRE(whileReader->getAllWhiles().empty());
    }

    SECTION("getAllWhiles: Non-empty") {
        whileWriter->insertWhile(7);
        whileWriter->insertWhile(8);
        REQUIRE(whileReader->getAllWhiles() == std::unordered_set<int>{7, 8});
        whileWriter->clear();
    }
}
