#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: ProcedureReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    // Use ProcedureWriter to directly populate procedures
    auto procedureWriter = pkbManager->getPKBWriterManager()->getProcedureWriter();

    // Clearing the store before populating it to ensure a clean state
    procedureWriter->clear();

    // Directly populating some procedures for retrieval tests
    procedureWriter->insertProcedure("proc1");
    procedureWriter->insertProcedure("proc2");
    procedureWriter->insertProcedure("assign");
    procedureWriter->insertProcedure("call");

    auto procedureReader = pkbManager->getPKBReaderManager()->getProcedureReader();

    SECTION("Verify retrieval of all procedures") {
        std::unordered_set<std::string> expectedProcedures = {"proc1", "proc2", "assign", "call"};
        auto retrievedProcedures = procedureReader->getAllProcedures();
        REQUIRE(retrievedProcedures == expectedProcedures);
    }

    SECTION("Check specific procedures exist") {
        REQUIRE(procedureReader->hasProcedure("proc1") == true);
        REQUIRE(procedureReader->hasProcedure("proc2") == true);
        REQUIRE(procedureReader->hasProcedure("assign") == true);
        REQUIRE(procedureReader->hasProcedure("nonExistentProc") == false); // Verify a non-existent procedure
    }

    SECTION("Check if ProcedureStore is empty") {
        REQUIRE(procedureReader->isEmpty() == false);
    }

    SECTION("Verify retrieval of procedures by name") {
        REQUIRE(procedureReader->hasProcedure("proc1") == true);
        REQUIRE(procedureReader->hasProcedure("proc2") == true);
        REQUIRE(procedureReader->hasProcedure("nonExistentProc") == false); // Test for a procedure that doesn't exist
    }

    SECTION("Verify store is cleared correctly") {
        procedureWriter->clear(); // Clear all procedures
        REQUIRE(procedureReader->isEmpty() == true);
    }


    // procedureWriter->clear();
}
