#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "sp/SourceProcessor.h"
#include "pkb/PKBManager.h"

TEST_CASE("sp/SourceProcessor: Procedures") {
    SECTION("Basic Procedure Names") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   print x;"
                                    "   print y;"
                                    "}"
                                    "procedure proc2 {"
                                    "   read x;"
                                    "   read y;"
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
        std::shared_ptr<ProcedureReader> procedureReader = pkbReaderManager->getProcedureReader();
        std::unordered_set<std::string> expectedProcedures = { "proc1", "proc2" };
        REQUIRE(procedureReader->getAllProcedures() == expectedProcedures);

        std::filesystem::remove(filename);
    }

    SECTION("Keywords as Procedure Names") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure assign { read x; }"
                                    "procedure call { read x; }"
                                    "procedure constant { read x; }"
                                    "procedure while { read x; }"
                                    "procedure if { read x; }"
                                    "procedure print { read x; }"
                                    "procedure read { read x; }"
                                    "procedure stmtLst { read x; }"
                                    "procedure variable { read x; }"
                                    "procedure stmt { read x; }"
                                    "procedure procedure { read x; }"
                                    "procedure program { read x; }"
                                    "procedure Follows { read x; }"
                                    "procedure FollowsT { read x; }"
                                    "procedure Parent { read x; }"
                                    "procedure ParentT { read x; }"
                                    "procedure Uses { read x; }"
                                    "procedure UsesP { read x; }"
                                    "procedure UsesS { read x; }"
                                    "procedure Modifies { read x; }"
                                    "procedure ModifiesP { read x; }"
                                    "procedure ModifiesS { read x; }"
                                    "procedure Calls { read x; }"
                                    "procedure CallsT { read x; }"
                                    "procedure Next { read x; }"
                                    "procedure NextT { read x; }"
                                    "procedure Affects { read x; }"
                                    "procedure AffectsT { read x; }";

        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<ProcedureReader> procedureReader = pkbReaderManager->getProcedureReader();
        std::unordered_set<std::string> expectedProcedures = { "assign", "call", "constant", "while", "if", "print", "read", "stmtLst", "variable", "stmt", "procedure", "program", "Follows", "FollowsT", "Parent", "ParentT", "Uses", "UsesP", "UsesS", "Modifies", "ModifiesP", "ModifiesS", "Calls", "CallsT", "Next", "NextT", "Affects", "AffectsT" };
        REQUIRE(procedureReader->getAllProcedures() == expectedProcedures);

        std::filesystem::remove(filename);
    }

    SECTION("Invalid SIMPLE Program") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   print x;"
                                    "   print y;";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        REQUIRE_THROWS_WITH(sp.parseSIMPLE(), "Error: Tried to parse statement, but input statement is not Assign, Call, Print, Read, If, or While statement.");
        std::filesystem::remove(filename);
    }
}