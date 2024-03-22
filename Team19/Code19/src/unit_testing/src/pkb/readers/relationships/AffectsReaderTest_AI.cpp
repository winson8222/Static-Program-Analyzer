#include "catch.hpp"
#include "pkb/PKBManager.h"


TEST_CASE("pkb/readers/relationships/AffectsReader") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<AffectsReader> affectsReader = pkbReaderManager->getAffectsReader();
    std::shared_ptr<UsesSWriter> usesSWriter = pkbManager->getPKBWriterManager()->getUsesSWriter();
    std::shared_ptr<ModifiesSWriter> modifiesSWriter = pkbManager->getPKBWriterManager()->getModifiesSWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbManager->getPKBWriterManager()->getAssignWriter();
    std::shared_ptr<NextWriter> nextWriter = pkbManager->getPKBWriterManager()->getNextWriter();
	std::shared_ptr<IfWriter> ifWriter = pkbManager->getPKBWriterManager()->getIfWriter();
	std::shared_ptr<WhileWriter> whileWriter = pkbManager->getPKBWriterManager()->getWhileWriter();
    auto pkbCacheManager = pkbManager->getPKBCacheManager();
    // Source code being tested
	/*
	 procedure main {
01	 	x = 0;
02      i = 5;
03      while (i!=0) {
04          x = x + 2*y;
05          call Third;
06          i = i - 1; }
07      if (x==1) then {
08          x = x+1; }
          else {
09          z = 1; }
10      z = z + x + i;
11      y = z + 2;
12      x = x * y + z;
	 */
	whileWriter->insertWhile(3);
	ifWriter->insertIf(7);

    usesSWriter->addRelationship(4, "y");
    usesSWriter->addRelationship(4, "x");
    usesSWriter->addRelationship(5, "Third");
    usesSWriter->addRelationship(6, "i");
    usesSWriter->addRelationship(7, "x");
    usesSWriter->addRelationship(8, "x");
    usesSWriter->addRelationship(10, "z");
    usesSWriter->addRelationship(10, "x");
    usesSWriter->addRelationship(10, "i");
    usesSWriter->addRelationship(11, "z");
    usesSWriter->addRelationship(12, "x");
    usesSWriter->addRelationship(12, "y");
    usesSWriter->addRelationship(12, "z");

    nextWriter->addRelationship(1, 2);
    nextWriter->addRelationship(2, 3);
    nextWriter->addRelationship(3, 4);
    nextWriter->addRelationship(4, 5);
    nextWriter->addRelationship(5, 6);
    nextWriter->addRelationship(6, 3);
    nextWriter->addRelationship(3, 7);
    nextWriter->addRelationship(7, 8);
    nextWriter->addRelationship(7, 9);
    nextWriter->addRelationship(8, 10);
    nextWriter->addRelationship(9, 10);
    nextWriter->addRelationship(10, 11);
    nextWriter->addRelationship(11, 12);

    assignWriter->addEntity(1);
    assignWriter->addEntity(2);
    assignWriter->addEntity(4);
    assignWriter->addEntity(6);
    assignWriter->addEntity(8);
    assignWriter->addEntity(9);
    assignWriter->addEntity(10);
    assignWriter->addEntity(11);
    assignWriter->addEntity(12);

    modifiesSWriter->addRelationship(1, "x");
    modifiesSWriter->addRelationship(2, "i");
    modifiesSWriter->addRelationship(4, "x");
    modifiesSWriter->addRelationship(6, "i");
	modifiesSWriter->addRelationship(7, "x");
	modifiesSWriter->addRelationship(7, "z");
    modifiesSWriter->addRelationship(8, "x");
    modifiesSWriter->addRelationship(9, "z");
    modifiesSWriter->addRelationship(10, "z");
    modifiesSWriter->addRelationship(11, "y");
    modifiesSWriter->addRelationship(12, "x");

    SECTION("Empty") {
        REQUIRE(affectsReader->getAffected(1).empty());
        REQUIRE(affectsReader->getAffecting(1).empty());
        REQUIRE(affectsReader->getAllAffected().empty());
        REQUIRE(affectsReader->getAllAffecting().empty());
        REQUIRE(affectsReader->isEmpty());
    }

    pkbCacheManager->populateCache();

    SECTION("getAllAffecting") {
        std::unordered_set<int> expected = { 1, 2, 4, 6, 8, 9, 10, 11 };
        REQUIRE(affectsReader->getAllAffecting() == expected);
    }

	SECTION("getAllAffected") {
        std::unordered_set<int> expected = { 4, 6, 8, 10, 11, 12 };
        REQUIRE(affectsReader->getAllAffected() == expected);
    }

    SECTION("getAffecting") {
        REQUIRE(affectsReader->getAffecting(1).empty());
        REQUIRE(affectsReader->getAffecting(2).empty());
        REQUIRE(affectsReader->getAffecting(3).empty());
        REQUIRE(affectsReader->getAffecting(4) == std::unordered_set<int>{ 1, 4 });
        REQUIRE(affectsReader->getAffecting(5).empty());
        REQUIRE(affectsReader->getAffecting(6) == std::unordered_set<int>{ 2, 6 });
        REQUIRE(affectsReader->getAffecting(7).empty());
        REQUIRE(affectsReader->getAffecting(8) == std::unordered_set<int>{ 1, 4 });
        REQUIRE(affectsReader->getAffecting(9).empty());
        REQUIRE(affectsReader->getAffecting(10) == std::unordered_set<int>{ 1, 2, 4, 6, 8, 9});
        REQUIRE(affectsReader->getAffecting(11) == std::unordered_set<int>{ 10 });
        REQUIRE(affectsReader->getAffecting(12) == std::unordered_set<int>{ 1, 4, 8, 10, 11 });
    }

	SECTION("getAffected") {
		REQUIRE(affectsReader->getAffected(1) == std::unordered_set<int>{ 4, 8, 10, 12 });
		REQUIRE(affectsReader->getAffected(2) == std::unordered_set<int>{ 6, 10 });
		REQUIRE(affectsReader->getAffected(3).empty());
		REQUIRE(affectsReader->getAffected(4) == std::unordered_set<int>{ 4, 8, 10, 12 });
		REQUIRE(affectsReader->getAffected(5).empty());
		REQUIRE(affectsReader->getAffected(6) == std::unordered_set<int>{ 6, 10 });
		REQUIRE(affectsReader->getAffected(7).empty());
		REQUIRE(affectsReader->getAffected(8) == std::unordered_set<int>{ 10, 12 });
		REQUIRE(affectsReader->getAffected(9) == std::unordered_set<int>{ 10 });
		REQUIRE(affectsReader->getAffected(10) == std::unordered_set<int>{ 11, 12 });
		REQUIRE(affectsReader->getAffected(11) == std::unordered_set<int>{ 12 });
		REQUIRE(affectsReader->getAffected(12).empty());
	}
}