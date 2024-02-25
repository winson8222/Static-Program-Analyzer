//#include "catch.hpp"
//#include <memory>
//#include "pkb/PKBManager.h"
//#include "../Utils.h" // Assuming Utils.h is available for utility functions
//
//// Fixture class for setting up PKB and Procedure tests
//class ProcedureReaderFixture {
//public:
//    std::shared_ptr<PKBManager> pkbManager;
//    std::shared_ptr<ProcedureWriter> procedureWriter;
//
//    ProcedureReaderFixture() : pkbManager(std::make_shared<PKBManager>()) {
//        procedureWriter = pkbManager->getPKBWriterManager()->getProcedureWriter();
//        // Clearing previous data for a clean state
//        procedureWriter->clear();
//    }
//
//    void populateProcedures() {
//        // Populating procedures for retrieval tests
//        procedureWriter->insertProcedure("proc1");
//        procedureWriter->insertProcedure("proc2");
//        procedureWriter->insertProcedure("assign");
//        procedureWriter->insertProcedure("call");
//    }
//};
//
//TEST_CASE_METHOD(ProcedureReaderFixture, "qps/QueryProcessingSubsystem: ProcedureReader Integration Test", "[QPS][PKB][Procedure]") {
//    populateProcedures();
//
//    SECTION("Verify retrieval of all procedures via QPS") {
//        std::string query = "procedure p; Select p";
//        auto results = Utils::getResultsFromQuery(query, pkbManager->getPKBReaderManager());
//        std::unordered_set<std::string> expectedResults = {"proc1", "proc2", "assign", "call"};
//        REQUIRE(results == expectedResults);
//    }
//
////    SECTION("Check for the existence of a specific procedure") {
////        std::string queryExists = "procedure p; Select BOOLEAN such that Modifies(p, _)";
////        auto resultsExists = Utils::getResultsFromQuery(queryExists, pkbManager->getPKBReaderManager());
////        // Assuming 'Modifies' is just a placeholder for any relevant condition to check existence
////        REQUIRE(!resultsExists.empty()); // Adjust based on actual data and query capabilities
////    }
////
////    SECTION("Test for a non-existent procedure") {
////        std::string queryNonExistent = "procedure p; Select BOOLEAN such that Modifies(p, \"nonExistentVar\")";
////        auto resultsNonExistent = Utils::getResultsFromQuery(queryNonExistent, pkbManager->getPKBReaderManager());
////        // Assuming 'Modifies' is a placeholder; adjust the query to fit actual testing needs
////        REQUIRE(resultsNonExistent.find("FALSE") != resultsNonExistent.end());
////    }
//}
