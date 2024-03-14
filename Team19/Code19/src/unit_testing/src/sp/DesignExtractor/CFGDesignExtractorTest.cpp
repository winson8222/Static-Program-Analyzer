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

TEST_CASE("Next Extractors") {
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

	SECTION("Test simple next statements extractors") {
		std::shared_ptr<CFGNode> assign1 = std::make_shared<CFGNode>(1);
		std::shared_ptr<CFGNode> assign2 = std::make_shared<CFGNode>(2);
		assign1->addChild(assign2);
		NextExtractor nextExtractor(assign1, assign2, pkbWriterManager->getNextWriter());
		nextExtractor.extract();

		std::unordered_set<int> expectedNextOf1 = { 2 };
		REQUIRE(pkbReaderManager->getNextReader()->getNext(1) == expectedNextOf1);

		std::shared_ptr<CFGNode> print3 = std::make_shared<CFGNode>(3);
		assign2->addChild(print3);
		NextExtractor nextExtractor2(assign2, print3, pkbWriterManager->getNextWriter());
		nextExtractor2.extract();

		std::unordered_set<int> expectedNexts2 = { 3 };
		REQUIRE(pkbReaderManager->getNextReader()->getNext(2) == expectedNexts2);

		std::unordered_set<int> expectedNexts = { 2, 3 };
		REQUIRE(pkbReaderManager->getNextReader()->getAllNext() == expectedNexts);

		std::unordered_set<int> expectedPrevs = { 1, 2 };
		REQUIRE(pkbReaderManager->getNextReader()->getAllPrevious() == expectedPrevs);

		std::unordered_set<int> expectedNextsTOf1 = { 2, 3 };
		REQUIRE(pkbReaderManager->getNextTReader()->getNextT(1) == expectedNextsTOf1);

		std::shared_ptr<CFGNode> while4 = std::make_shared<CFGNode>(4);
		std::shared_ptr<CFGNode> assign5 = std::make_shared<CFGNode>(5);
		std::shared_ptr<CFGNode> if6 = std::make_shared<CFGNode>(6);
		while4->addChild(assign5);
		while4->addChild(if6);

		for (auto node : while4->getChildren()) {
			NextExtractor nextExtractor(while4, node, pkbWriterManager->getNextWriter());
			nextExtractor.extract();
		}
		std::unordered_set<int> expectedNextsTof4 = { 5, 6 };
		REQUIRE(pkbReaderManager->getNextReader()->getNext(4) == expectedNextsTof4);

		std::shared_ptr<CFGNode> assign7 = std::make_shared<CFGNode>(7);
		std::shared_ptr<CFGNode> assign8 = std::make_shared<CFGNode>(8);
		std::shared_ptr<CFGNode> assign9 = std::make_shared<CFGNode>(9);
		assign7->addChild(assign9);
		assign8->addChild(assign9);
		NextExtractor nextExtractor3(assign7, assign9, pkbWriterManager->getNextWriter());
		nextExtractor3.extract();
		NextExtractor nextExtractor4(assign8, assign9, pkbWriterManager->getNextWriter());
		nextExtractor4.extract();
		std::unordered_set<int> expectedPrevTo9 = { 7, 8 };
		REQUIRE(pkbReaderManager->getNextReader()->getPrevious(9) == expectedPrevTo9);
	}

	SECTION("Test CFGVisitor") {
		std::shared_ptr<CFGNode> assign1 = std::make_shared<CFGNode>(1);
		std::shared_ptr<CFGNode> assign2 = std::make_shared<CFGNode>(2);
		assign1->addChild(assign2);
		std::shared_ptr<CFGNode> print3 = std::make_shared<CFGNode>(3);
		assign2->addChild(print3);
		std::shared_ptr<CFGNode> while4 = std::make_shared<CFGNode>(4);
		print3->addChild(while4);
		std::shared_ptr<CFGNode> assign5 = std::make_shared<CFGNode>(5);
		std::shared_ptr<CFGNode> if6 = std::make_shared<CFGNode>(6);
		while4->addChild(assign5);
		while4->addChild(if6);
		std::shared_ptr<CFGNode> assign7 = std::make_shared<CFGNode>(7);
		std::shared_ptr<CFGNode> assign8 = std::make_shared<CFGNode>(8);
		if6->addChild(assign7);
		if6->addChild(assign8);
		std::shared_ptr<CFGNode> assign9 = std::make_shared<CFGNode>(9);
		assign7->addChild(assign9);
		assign8->addChild(assign9);
		assign9->addChild(CFGNode::getDummyNode());

		std::vector<std::shared_ptr<CFGNode>> procs = { assign1 };
		CFGVisitor cfgVisitor(procs, pkbWriterManager);
		REQUIRE_NOTHROW(cfgVisitor.visit());

		std::unordered_set<int> expectedNextOf3= { 4 };
		REQUIRE(pkbReaderManager->getNextReader()->getNext(3) == expectedNextOf3);

		std::unordered_set<int> expectedPrevOf9 = {7, 8};
		REQUIRE(pkbReaderManager->getNextReader()->getPrevious(9) == expectedPrevOf9);

		std::unordered_set<int> expectedAllNexts = { 2, 3, 4, 5, 6, 7, 8, 9 };
		REQUIRE(pkbReaderManager->getNextReader()->getAllNext() == expectedAllNexts);

		std::unordered_set<int> expectedAllPrevs = { 1, 2, 3, 4, 6, 7, 8 };
		REQUIRE(pkbReaderManager->getNextReader()->getAllPrevious() == expectedAllPrevs);
	}
}