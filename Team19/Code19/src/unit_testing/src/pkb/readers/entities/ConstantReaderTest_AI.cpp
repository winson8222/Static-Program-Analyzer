#include "catch.hpp"
#include "pkb/PKBManager.h"

TEST_CASE("pkb/readers/entities/ConstantReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto pkbReader = pkbManager->getPKBReaderManager();
    auto pkbWriter = pkbManager->getPKBWriterManager();
    auto constantReader = pkbReader->getConstantReader();
    auto constantWriter = pkbWriter->getConstantWriter();

    SECTION("getAllConstants: Empty") {
        REQUIRE(constantReader->getAllConstants().empty());
    }

    SECTION("getAllConstants: Non-empty") {
        constantWriter->insertConstant(5);
        constantWriter->insertConstant(6);
        REQUIRE(constantReader->getAllConstants() == std::unordered_set<int>{5, 6});
        constantWriter->clear();
    }
}
