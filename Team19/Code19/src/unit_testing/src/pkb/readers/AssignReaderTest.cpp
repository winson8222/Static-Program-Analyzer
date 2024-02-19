#include "catch.hpp"
#include "pkb/PKBManager.h"

TEST_CASE("AssignReader: Basic Functionality") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto pkbReader = pkbManager->getPKBReaderManager();
    auto pkbWriter = pkbManager->getPKBWriterManager();
    auto assignReader = pkbReader->getAssignReader();
    auto assignWriter = pkbWriter->getAssignWriter();

    SECTION("getAllAssigns: Empty") {
        REQUIRE(assignReader->getAllAssigns().empty());
    }

    SECTION("getAllAssigns: Non-empty") {
        assignWriter->insertAssign(1);
        assignWriter->insertAssign(2);
        REQUIRE(assignReader->getAllAssigns() == std::unordered_set<int>{1, 2});
        assignWriter->clear();
    }
}
