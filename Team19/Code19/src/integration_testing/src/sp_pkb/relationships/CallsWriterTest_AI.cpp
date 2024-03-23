#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Calls Procedure") {
    SECTION("Uses in Procedure and Call for invokes") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
            "   x = 1 + u;"     // 1
            "   while (x < 10) {"   // 2
            "       y = 2 + x; "    // 3
            "       x = p + 1;}"    // 4
            "    if (x > 10) then {"        // 5
            "       z = 3 + x; "        // 6
            "       t = 4 + y + x + i + u; "    // 7
            "       } else {"
            "           z = 3 + x; "    // 8
            "           t = 4 + y + x + i + u; "    // 9
            "       while (x < 10) {"   // 10
            "           x = 3 + y; }}}"   // 11
            "procedure proc2 {"
            "   z = 3 + x; "    // 12
            "   call proc1; }"     // 13
            "procedure proc3 {"
            "me = meme;"    // 14
            "call proc2; }"// 15
            "procedure proc4 {"
            "call proc2;"   // 16
            "call proc3; }";    // 17
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
        std::shared_ptr<CallProcNameReader> callProcNameReader = pkbReaderManager->getCallProcNameReader();
        std::shared_ptr<UsesPReader> usesPReader = pkbReaderManager->getUsesPReader();
        std::shared_ptr<UsesSReader> usesSReader = pkbReaderManager->getUsesSReader();
        std::shared_ptr<ModifiesPReader> modifiesPReader = pkbReaderManager->getModifiesPReader();
        std::shared_ptr<ModifiesSReader> modifiesSReader = pkbReaderManager->getModifiesSReader();

        std::string expectedCall1 = "proc2";
        REQUIRE(callProcNameReader->getCalledProcedureName(16) == expectedCall1);

        std::string expectedCall2 = "proc3";
        REQUIRE(callProcNameReader->getCalledProcedureName(17) == expectedCall2);

        std::unordered_set<int> expectedCallers1 = {15, 16};
        REQUIRE(callProcNameReader->getCallers("proc2") == expectedCallers1);

        std::string expectedCall3 = "proc1";
        REQUIRE(callProcNameReader->isCalled(13, expectedCall3));

        std::unordered_set<std::string> expectedCalls = {"proc2", "proc3", "proc4"};
        REQUIRE(callsTReader->getTransitiveCallersOfProcedure("proc1") == expectedCalls);

        std::unordered_set<std::string> expectedCalls2 = { "proc1", "proc2", "proc3" };
        REQUIRE(callsTReader->getTransitivelyCalledProcedures("proc4") == expectedCalls2);

        std::unordered_set<std::string> expectedCalls3 = { "proc1" };
        REQUIRE(callsReader->getDirectlyCalledProcedures("proc2") == expectedCalls3);

        std::unordered_set<std::string> expectedCalls4 = { "proc4" };
        REQUIRE(callsReader->getDirectCallersOfProcedure("proc3") == expectedCalls4);

        std::unordered_set<std::string> expectedUse1 = { "meme", "x", "y", "u", "p", "i"};
        REQUIRE(usesPReader->getAllVariablesUsedByProc("proc3") == expectedUse1);
        REQUIRE(usesSReader->getAllVariablesUsedByStmt(17) == expectedUse1);

        std::unordered_set<std::string> expectedModify1 = {"me", "z", "x", "t", "y"};
        REQUIRE(modifiesPReader->getAllVariablesModifiedByProc("proc3") == expectedModify1);
        REQUIRE(modifiesSReader->getAllVariablesModifiedByStmt(17) == expectedModify1);

        std::unordered_set<std::string> expectedUse2 = { "x", "y", "u", "p", "i" };
        REQUIRE(usesSReader->getAllVariablesUsedByStmt(13) == expectedUse2);

        std::unordered_set<std::string> expectedModify2 = { "z", "x", "y", "t"};
        REQUIRE(modifiesSReader->getAllVariablesModifiedByStmt(13) == expectedModify2);
    }
}