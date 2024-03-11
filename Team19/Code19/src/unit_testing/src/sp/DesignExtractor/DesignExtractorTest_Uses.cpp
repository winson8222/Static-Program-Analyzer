#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/AST/ASTNode.h"
#include "sp/Parser/SimpleParserFacade.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
#include "catch.hpp"
#include <filesystem>
#include <unordered_set>
#include <vector>

TEST_CASE("sp/SourceProcessor: Uses(unit)") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    std::shared_ptr<UsesSReader> usesSReader = pkbManager->getPKBReaderManager()->getUsesSReader();
    std::shared_ptr<UsesPReader> usesPPReader = pkbManager->getPKBReaderManager()->getUsesPReader();

    SECTION("Basic Uses") {
        SECTION("Test assign") {
            std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 1, "z");
            std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x");
            std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "y");
            UsesExtractor usesExtractor(ast1, ast2, pkbWriterManager);
            usesExtractor.extract();
            UsesExtractor usesExtractor2(ast1, ast3, pkbWriterManager);
            usesExtractor2.extract();

            REQUIRE(usesSReader->doesStmtUseVariable(1, "x"));
            REQUIRE(usesSReader->doesStmtUseVariable(1, "y"));
            REQUIRE(!usesSReader->doesStmtUseVariable(1, "z"));
        }

        SECTION("Test print") {
            std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::PRINT, 2, "print");
            std::shared_ptr<ASTNode> ast4 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 2, "y");
            UsesExtractor usesExtractor3(ast3, ast4, pkbWriterManager);
            usesExtractor3.extract();
            REQUIRE(usesSReader->doesStmtUseVariable(2, "y"));
        }

        SECTION("Test ifs") {
            std::shared_ptr<ASTNode> ast5 = std::make_shared<ASTNode>(ASTNodeType::IF_ELSE_THEN, 3, "ifs");
            std::shared_ptr<ASTNode> ast6 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 4, "z");
            UsesExtractor usesExtractor4(ast5, ast6, pkbWriterManager);
            usesExtractor4.extract();
            REQUIRE(usesSReader->doesStmtUseVariable(3, "z"));
        }

        SECTION("Test while") {
            std::shared_ptr<ASTNode> ast7 = std::make_shared<ASTNode>(ASTNodeType::WHILE, 5, "while");
            std::shared_ptr<ASTNode> ast8 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 6, "t");
            UsesExtractor usesExtractor5(ast7, ast8, pkbWriterManager);
            usesExtractor5.extract();
            REQUIRE(usesSReader->doesStmtUseVariable(5, "t"));
        }

        SECTION("Test procedure") {
            std::shared_ptr<ASTNode> ast9 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 0, "proc");
            std::shared_ptr<ASTNode> ast10 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 0, "x");
            UsesExtractor usesExtractor6(ast9, ast10, pkbWriterManager);
            usesExtractor6.extract();
            REQUIRE(usesPPReader->doesProcUseVariable("proc", "x"));
        }

        SECTION("Test read") {
            std::shared_ptr<ASTNode> ast11 = std::make_shared<ASTNode>(ASTNodeType::READ, 7, "read");
			std::shared_ptr<ASTNode> ast12 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 7, "x");
			UsesExtractor usesExtractor7(ast11, ast12, pkbWriterManager);
			usesExtractor7.extract();
			REQUIRE(!usesSReader->doesStmtUseVariable(7, "x"));
        }

        SECTION("Test call") {
			std::shared_ptr<ASTNode> ast13 = std::make_shared<ASTNode>(ASTNodeType::CALL, 8, "call");
			std::shared_ptr<ASTNode> ast14 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 8, "x");
			UsesExtractor usesExtractor8(ast13, ast14, pkbWriterManager);
			usesExtractor8.extract();
			REQUIRE(usesSReader->doesStmtUseVariable(8, "x"));
        }
    }

    SECTION("Advanced Uses") {
        std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 0, "proc");
        std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::IF_ELSE_THEN, 1, "ifs");
        std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::WHILE, 2, "while");
        std::shared_ptr<ASTNode> ast4 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 3, "x");
        std::shared_ptr<ASTNode> ast5 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "x");
        std::vector<std::shared_ptr<ASTNode>> asts = { ast1, ast2, ast3, ast4 };

        VariableVisitor variableVisitor(ast5, pkbWriterManager);
        variableVisitor.setUsedContext(asts, ast5);
        variableVisitor.visit();

        REQUIRE(usesPPReader->doesProcUseVariable("proc", "x"));
        REQUIRE(usesSReader->doesStmtUseVariable(1, "x"));
        REQUIRE(usesSReader->doesStmtUseVariable(2, "x"));
        REQUIRE(usesSReader->doesStmtUseVariable(3, "x"));

        std::unordered_set<int> expected = usesSReader->getAllStmtsThatUseVariable("x");
        std::unordered_set<int> actual = { 1, 2, 3 };
        REQUIRE(expected == actual);
    }

    SECTION("Advanced Uses (call and procedure)") {
        std::shared_ptr<ASTNode> ast0 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 0, "proc1");
		std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 0, "proc2");
		std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::CALL, 1, "call");
		std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x");
		std::vector<std::shared_ptr<ASTNode>> asts = { ast0, ast1, ast2 };

		VariableVisitor variableVisitor(ast3, pkbWriterManager);
		variableVisitor.setUsedContext(asts, ast3);
		variableVisitor.visit();

		REQUIRE(usesPPReader->doesProcUseVariable("proc1", "x"));
        REQUIRE(usesPPReader->doesProcUseVariable("proc2", "x"));
		REQUIRE(usesSReader->doesStmtUseVariable(1, "x"));
    }
}