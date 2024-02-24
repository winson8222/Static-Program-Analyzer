#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "sp/SourceProcessor.h"
#include "pkb/PKBManager.h"

TEST_CASE("sp/SourceProcessor: Variables") {
    SECTION("Basic Variable Names") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1;"
                                    "   y = 2;"
                                    "}"
                                    "procedure proc2 {"
                                    "   x = 3;"
                                    "   y = 4;"
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
        std::shared_ptr<VariableReader> variableReader = pkbReaderManager->getVariableReader();
        std::unordered_set<std::string> expectedVariables = { "x", "y" };
        REQUIRE(variableReader->getAllVariables() == expectedVariables);

        std::filesystem::remove(filename);
    }

    SECTION("Keywords as Variable Names") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure assign {"
                                    "   read = 1;"
                                    "   print = 2;"
                                    "   call = 3;"
                                    "   while = 4;"
                                    "   if = 5;"
                                    "   assign = 6;"
                                    "   constant = 7;"
                                    "   variable = 8;"
                                    "   stmtLst = 9;"
                                    "   stmt = 10;"
                                    "   procedure = 11;"
                                    "   program = 12;"
                                    "   Follows = 13;"
                                    "   FollowsT = 14;"
                                    "   Parent = 15;"
                                    "   ParentT = 16;"
                                    "   Uses = 17;"
                                    "   UsesP = 18;"
                                    "   UsesS = 19;"
                                    "   Modifies = 20;"
                                    "   ModifiesP = 21;"
                                    "   ModifiesS = 22;"
                                    "   Calls = 23;"
                                    "   CallsT = 34;"
                                    "   Next = 25;"
                                    "   NextT = 26;"
                                    "   Affects = 27;"
                                    "   AffectsT = 28;"
                                    "   pattern = 21;"
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
        std::shared_ptr<VariableReader> variableReader = pkbReaderManager->getVariableReader();
        std::unordered_set<std::string> expectedVariables = { "read", "print", "call", "while", "if", "assign", "constant", "variable", "stmtLst", "stmt", "procedure", "program", "Follows", "FollowsT", "Parent", "ParentT", "Uses", "UsesP", "UsesS", "Modifies", "ModifiesP", "ModifiesS", "Calls", "CallsT", "Next", "NextT", "Affects", "AffectsT", "pattern" };
        REQUIRE(variableReader->getAllVariables() == expectedVariables);

        std::filesystem::remove(filename);
    }

    SECTION("Variable Name starting with Digits") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   1x = 1;"
                                    "   2y = 2;"
                                    "}"
                                    "procedure proc2 {"
                                    "   3x = 3;"
                                    "   4y = 4;"
                                    "}";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        REQUIRE_THROWS_WITH(SourceProcessor(filename, pkbManager), "Error: Invalid SIMPLE syntax.");

        std::filesystem::remove(filename);
    }
}
