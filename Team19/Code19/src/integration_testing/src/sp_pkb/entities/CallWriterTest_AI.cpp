#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Calls") {
    SECTION("Basic Calls") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1;"
                                    "   call proc2;"
                                    "}"
                                    "procedure proc2 {"
                                    "   z = 1;"
                                    "   call proc3;"
                                    "}"
                                    "procedure proc3 {"
                                    "   y = 6 * z;"
                                    "}";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<CallReader> callReader = pkbReaderManager->getCallReader();
        std::unordered_set<int> expectedCalls = { 2, 4 };
        REQUIRE(callReader->getAllCalls() == expectedCalls);
        std::filesystem::remove(filename);
    }

    SECTION("Advanced Calls") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
            "   x = y + z - 3;"     // 1
            "   call proc2;"        // 2
            "}"
            "procedure proc2 {"
            "   a = 10 * b - c;"    // 3
            "while (b != 0) {"      // 4
            "   print d;"           // 5
            "   read e;}"           // 6
            "   call proc3;"        // 7
            "}"
            "procedure proc3 {"
            "   m = n / p;"         // 8
            "}"
            "procedure proc4 {"
            "   call proc1;"        // 9
            "}";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<CallReader> callReader = pkbReaderManager->getCallReader();
        std::shared_ptr<CallsReader> callsReader = pkbReaderManager->getCallsReader();
        std::shared_ptr<CallsTReader> callsTReader = pkbReaderManager->getCallsTReader();

        std::unordered_set<int> expectedCalls = { 2, 7, 9 };
        REQUIRE(callReader->getAllCalls() == expectedCalls);

        std::unordered_set<std::string> expectedCallsProc = { "proc1", "proc2", "proc3" };
        REQUIRE(callsReader->getAllDirectCallees() == expectedCallsProc);

        std::unordered_set<std::string> expectedCallers = { "proc4", "proc1", "proc2" };
        REQUIRE(callsReader->getAllDirectCallers() == expectedCallers);

        REQUIRE(callsReader->getDirectCallersOfProcedure("proc1") == std::unordered_set<std::string>({ "proc4" }));
        REQUIRE(callsReader->getDirectlyCalledProcedures("proc1") == std::unordered_set<std::string>({"proc2"}));

        std::unordered_set<std::string> expectedCallsTProc = { "proc1", "proc2", "proc3" };
        REQUIRE(callsTReader->getAllTransitiveCallees() == expectedCallsProc);

        std::unordered_set<std::string> expectedCallersT = { "proc4", "proc1", "proc2" };
        REQUIRE(callsTReader->getAllTransitiveCallers() == expectedCallers);

        REQUIRE(callsTReader->getTransitiveCallersOfProcedure("proc3") == std::unordered_set<std::string>({ "proc1", "proc2", "proc4" }));
        REQUIRE(callsTReader->getTransitivelyCalledProcedures("proc1") == std::unordered_set<std::string>({ "proc2", "proc3" }));
        std::filesystem::remove(filename);
    }
}