#include "catch.hpp"
#include "sp/Parser/SimpleCallLinker.h"

TEST_CASE("Testing SimpleCallLinker class", "[SimpleLineManager]") {
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNodeType::PROGRAMS, 0, "program");
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 0, "proc1");
	std::shared_ptr<ASTNode> stmtLst1 = std::make_shared<ASTNode>(ASTNodeType::STATEMENT_LIST, 0, "stmtLst1");
	std::shared_ptr<ASTNode> print = std::make_shared<ASTNode>(ASTNodeType::PRINT, 1, "print");
	std::shared_ptr<ASTNode> var = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x");
	print->addChild(var);
	stmtLst1->addChild(print);
	proc1->addChild(stmtLst1);

	std::shared_ptr<ASTNode> proc2 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 0, "proc2");
	std::shared_ptr<ASTNode> stmtLst2 = std::make_shared<ASTNode>(ASTNodeType::STATEMENT_LIST, 0, "stmtLst1");
	std::shared_ptr<ASTNode> call = std::make_shared<ASTNode>(ASTNodeType::CALL, 1, "call");
	std::shared_ptr<ASTNode> p2 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "proc1");
	call->addChild(p2);
	stmtLst2->addChild(call);
	proc2->addChild(stmtLst2);

	root->addChild(proc1);
	root->addChild(proc2);
	SimpleCallLinker linker(root);
	REQUIRE_NOTHROW(linker.linkAllCallsToProcedure());
	REQUIRE(call->getChildByIndex(0)->getType() == ASTNodeType::PROCEDURE);
	REQUIRE(call->getChildByIndex(0) == proc1);
}