#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/AST/ASTNode.h"
#include "sp/Parser/SimpleParserFacade.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
#include "catch.hpp"
#include <fstream>
#include <filesystem>
#include <unordered_set>
#include <vector>

TEST_CASE("Calls") {
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

	SECTION("Test call statements") {
		std::shared_ptr<ASTNode> call = std::make_shared<ASTNode>(ASTNodeType::CALL, 1, "call");
		CallExtractor callExtractor(call, pkbWriterManager->getCallWriter());
		callExtractor.extract();
		std::shared_ptr<ASTNode> call2 = std::make_shared<ASTNode>(ASTNodeType::CALL, 4, "call");
		CallExtractor callExtractor2(call2, pkbWriterManager->getCallWriter());
		callExtractor2.extract();

		std::unordered_set<int> expectedCalls = { 1, 4 };
		REQUIRE(pkbReaderManager->getCallReader()->getAllCalls() == expectedCalls);
	}

	SECTION("Test call statements") {
		std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 1, "proc1");
		std::shared_ptr<ASTNode> proc2 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 2, "proc2");
		CallsPExtractor callExtractor(proc1, proc2, pkbWriterManager->getCallsWriter());
		callExtractor.extract();

		std::unordered_set<std::string> expectedCallers = { "proc1" };
		std::unordered_set<std::string> expectedCallees = { "proc2" };
		REQUIRE(pkbReaderManager->getCallsReader()->getAllDirectCallees() == expectedCallees);
		REQUIRE(pkbReaderManager->getCallsReader()->getAllDirectCallers() == expectedCallers);
	}

	SECTION("Test call transitive statements") {
		std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 1, "proc1");
		std::shared_ptr<ASTNode> proc2 = std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 2, "proc2");
		CallsTExtractor callExtractor(proc1, proc2, pkbWriterManager->getCallsTWriter());
		callExtractor.extract();

		std::unordered_set<std::string> expectedCallers = { "proc1" };
		std::unordered_set<std::string> expectedCallees = { "proc2" };
		REQUIRE(pkbReaderManager->getCallsTReader()->getAllTransitiveCallees() == expectedCallees);
		REQUIRE(pkbReaderManager->getCallsTReader()->getAllTransitiveCallers() == expectedCallers);
	}
}