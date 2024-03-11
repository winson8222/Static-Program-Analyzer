#include "catch.hpp"

#include "pkb/PKBManager.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
TEST_CASE("pkb/PKBCacheManager") {
	auto pkbManager = std::make_shared<PKBManager>();
	auto pkbCacheManager = pkbManager->getPKBCacheManager();
	auto pkbWriterManager = pkbManager->getPKBWriterManager();
	SECTION("NextT") {
		auto nextWriter = pkbWriterManager->getNextWriter();
		auto nextTReader = pkbManager->getPKBReaderManager()->getNextTReader();
		nextWriter->addNext(1, 2);
		nextWriter->addNext(2, 3);
		nextWriter->addNext(3, 4);
		nextWriter->addNext(4, 5);
		pkbCacheManager->populateCache();
		REQUIRE(nextTReader->getNextT(1) == std::unordered_set<int>{2, 3, 4, 5});
	}
}
// ai-gen end
