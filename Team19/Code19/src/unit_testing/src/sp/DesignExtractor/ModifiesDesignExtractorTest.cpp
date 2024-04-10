#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/AST/ASTNode.h"
#include "sp/Parser/SimpleParserFacade.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
#include "catch.hpp"
#include <unordered_set>
#include <vector>

TEST_CASE("sp/SourceProcessor: Modifies(unit)") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    std::shared_ptr<ModifiesSReader> modifiesSReader = pkbManager->getPKBReaderManager()->getModifiesSReader();
    std::shared_ptr<ModifiesPReader> modifiesPReader = pkbManager->getPKBReaderManager()->getModifiesPReader();
    ModifiesSExtractor modifiesExtractor1(pkbWriterManager->getModifiesSWriter());
    SECTION("Basic ModifiesS") {
        SECTION("Test assign") {
            std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 1, "x");
            std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x");
            
            modifiesExtractor1.extract(ast1, ast2);
            REQUIRE(modifiesSReader->doesStmtModifyVariable(1, "x"));
        }
        
        SECTION("Test read") {
            std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::READ, 2, "read");
            std::shared_ptr<ASTNode> ast4 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 2, "y");
            modifiesExtractor1.extract(ast3, ast4);
            REQUIRE(modifiesSReader->doesStmtModifyVariable(2, "y"));
        }
        
        SECTION("Test ifs") {
            std::shared_ptr<ASTNode> ast5 = std::make_shared<ASTNode>(ASTNodeType::IF_ELSE_THEN, 3, "ifs");
            std::shared_ptr<ASTNode> ast6 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 4, "z");
            modifiesExtractor1.extract(ast5, ast6);
            REQUIRE(modifiesSReader->doesStmtModifyVariable(3, "z"));
        }
        
        SECTION("Test while") {
            std::shared_ptr<ASTNode> ast7 = std::make_shared<ASTNode>(ASTNodeType::WHILE, 5, "while");
            std::shared_ptr<ASTNode> ast8 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 6, "t");
            modifiesExtractor1.extract(ast7, ast8);
            REQUIRE(modifiesSReader->doesStmtModifyVariable(5, "t"));
        }
        
        SECTION("Test procedure") {
            std::shared_ptr<ASTNode> ast9 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 0, "proc");
            std::shared_ptr<ASTNode> ast10 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 0, "x");
            ModifiesPExtractor modifiesExtractor1(pkbWriterManager->getModifiesPWriter());
            modifiesExtractor1.extract(ast9, ast10);
            REQUIRE(modifiesPReader->doesProcModifyVariable("proc", "x"));
        }

        SECTION("Test print") {
            std::shared_ptr<ASTNode> ast11 = std::make_shared<ASTNode>(ASTNodeType::PRINT, 7, "print");
			std::shared_ptr<ASTNode> ast12 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 7, "z");
        }

        SECTION("Test call") {
            std::shared_ptr<ASTNode> ast13 = std::make_shared<ASTNode>(ASTNodeType::CALL, 8, "call");
            std::shared_ptr<ASTNode> ast14 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 8, "z");
            modifiesExtractor1.extract(ast13, ast14);
            REQUIRE(modifiesSReader->doesStmtModifyVariable(8, "z"));
        }
    }

    SECTION("Advanced ModifiesS") {
        std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 0, "proc");
        std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::IF_ELSE_THEN, 1, "ifs");
        std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::WHILE, 2, "while");
        std::shared_ptr<ASTNode> ast4 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 3, "x");
        std::shared_ptr<ASTNode> ast5 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "x");
        std::vector<std::shared_ptr<ASTNode>> asts = {ast1, ast2, ast3, ast4};
        
        VariableVisitor variableVisitor(ast5, pkbWriterManager);
        variableVisitor.setModifiedContext(asts, ast5);
        variableVisitor.visit();

        REQUIRE(modifiesPReader->doesProcModifyVariable("proc", "x"));
        REQUIRE(modifiesSReader->doesStmtModifyVariable(1, "x"));
        REQUIRE(modifiesSReader->doesStmtModifyVariable(2, "x"));
        REQUIRE(modifiesSReader->doesStmtModifyVariable(3, "x"));

        std::unordered_set<int> expected = modifiesSReader->getAllStmtsThatModifyVariable("x");
        std::unordered_set<int> actual = {1, 2, 3};
        REQUIRE(expected == actual);
    }

    SECTION("Advanced Modifies with Call and Procedure") {
        std::shared_ptr<ASTNode> ast0 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 0, "proc1");
		std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 0, "proc2");
		std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::CALL, 1, "call");
		std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x");
		std::vector<std::shared_ptr<ASTNode>> asts = {ast0, ast1, ast2};
		
		VariableVisitor variableVisitor(ast3, pkbWriterManager);
		variableVisitor.setModifiedContext(asts, ast3);
		variableVisitor.visit();

		REQUIRE(modifiesPReader->doesProcModifyVariable("proc1", "x"));
        REQUIRE(modifiesPReader->doesProcModifyVariable("proc2", "x"));
		REQUIRE(modifiesSReader->doesStmtModifyVariable(1, "x"));
    }
}
