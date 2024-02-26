#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"
#include "../Utils.h" // Assuming Utils.h is available for utility functions

// Fixture class for setting up PKB and Procedure tests
class ProcedureReaderFixture {
public:
    std::shared_ptr<PKBManager> pkbManager;
    std::shared_ptr<ProcedureWriter> procedureWriter;

    ProcedureReaderFixture() : pkbManager(std::make_shared<PKBManager>()) {
        procedureWriter = pkbManager->getPKBWriterManager()->getProcedureWriter();
        // Clearing previous data for a clean state
        procedureWriter->clear();
    }

    void populateProcedures() {
        // Populating procedures for retrieval tests
        procedureWriter->insertProcedure("proc1");
        procedureWriter->insertProcedure("proc2");
        procedureWriter->insertProcedure("assign");
        procedureWriter->insertProcedure("call");
    }
};

TEST_CASE_METHOD(ProcedureReaderFixture, "qps/QueryProcessingSubsystem: ProcedureReader Integration Test", "[QPS][PKB][Procedure]") {
    populateProcedures();

    SECTION("Verify retrieval of all procedures via QPS") {
        std::string query = "procedure p; Select p";
        auto results = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
        std::unordered_set<std::string> expectedResults = {"proc1", "proc2", "assign", "call"};
        REQUIRE(results == expectedResults);
    }
}
