#include "catch.hpp"
#include "pkb/PKBManager.h"

TEST_CASE("ProcedureReader: Basic Functionality") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto procedureReader = pkbManager->getPKBReaderManager()->getProcedureReader();
    auto procedureWriter = pkbManager->getPKBWriterManager()->getProcedureWriter();

    SECTION("getAllProcedures: Empty") {
        REQUIRE(procedureReader->getAllProcedures().empty());
    }

    SECTION("getAllProcedures: Non-empty") {
        procedureWriter->insertProcedure("main");
        procedureWriter->insertProcedure("helper");
        REQUIRE(procedureReader->getAllProcedures() == std::unordered_set<std::string>{"main", "helper"});
        procedureWriter->clear();
    }
}
