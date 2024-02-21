#include "catch.hpp"
#include "pkb/PKBManager.h"

TEST_CASE("ReadReader: Basic Functionality") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto readReader = pkbManager->getPKBReaderManager()->getReadReader();
    auto readWriter = pkbManager->getPKBWriterManager()->getReadWriter();

    SECTION("getAllReads: Empty") {
        REQUIRE(readReader->getAllReads().empty());
    }

    SECTION("getAllReads: Non-empty") {
        readWriter->insertRead(3);
        readWriter->insertRead(4);
        REQUIRE(readReader->getAllReads() == std::unordered_set<int>{3, 4});
        readWriter->clear();
    }
}
