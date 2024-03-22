#include "catch.hpp"
#include <iostream>
#include "pkb/stores/relationships/types/AffectsStore.h"

TEST_CASE("pkb/stores/relationships/types/AffectsStore") {
    auto assignStore = std::make_shared<AssignStore>();
    auto nextStore = std::make_shared<NextStore>();
    auto usesSStore = std::make_shared<UsesSStore>();
    auto modifiesSStore = std::make_shared<ModifiesSStore>();
	auto whileStore = std::make_shared<WhileStore>();
	auto ifStore = std::make_shared<IfStore>();
    AffectsStore affectsStore(assignStore, nextStore, usesSStore, modifiesSStore, whileStore, ifStore);

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
12      x = x * y + z; }
     */

    SECTION("populateAffectsStore") {
        usesSStore->addRelationship(4, "y");
        usesSStore->addRelationship(4, "x");
        usesSStore->addRelationship(5, "Third");
        usesSStore->addRelationship(6, "i");
        usesSStore->addRelationship(7, "x");
        usesSStore->addRelationship(8, "x");
        usesSStore->addRelationship(10, "z");
        usesSStore->addRelationship(10, "x");
        usesSStore->addRelationship(10, "i");
        usesSStore->addRelationship(11, "z");
        usesSStore->addRelationship(12, "x");
        usesSStore->addRelationship(12, "y");
        usesSStore->addRelationship(12, "z");

        nextStore->addRelationship(1, 2);
        nextStore->addRelationship(2, 3);
        nextStore->addRelationship(3, 4);
        nextStore->addRelationship(4, 5);
        nextStore->addRelationship(5, 6);
        nextStore->addRelationship(6, 3);
        nextStore->addRelationship(3, 7);
        nextStore->addRelationship(7, 8);
        nextStore->addRelationship(7, 9);
        nextStore->addRelationship(8, 10);
        nextStore->addRelationship(9, 10);
        nextStore->addRelationship(10, 11);
        nextStore->addRelationship(11, 12);

        assignStore->addEntity(1);
        assignStore->addEntity(2);
        assignStore->addEntity(4);
        assignStore->addEntity(6);
        assignStore->addEntity(8);
        assignStore->addEntity(9);
        assignStore->addEntity(10);
        assignStore->addEntity(11);
        assignStore->addEntity(12);

        modifiesSStore->addRelationship(1, "x");
        modifiesSStore->addRelationship(2, "i");
        modifiesSStore->addRelationship(4, "x");
        modifiesSStore->addRelationship(6, "i");
		modifiesSStore->addRelationship(7, "x");
		modifiesSStore->addRelationship(7, "z");
        modifiesSStore->addRelationship(8, "x");
        modifiesSStore->addRelationship(9, "z");
        modifiesSStore->addRelationship(10, "z");
        modifiesSStore->addRelationship(11, "y");
        modifiesSStore->addRelationship(12, "x");

		ifStore->addEntity(7);
		whileStore->addEntity(3);
		
        affectsStore.populateAffectsStore();

        REQUIRE(affectsStore.getRelationshipsByKey(1) == std::unordered_set<int>{4, 8, 10, 12});
        REQUIRE(affectsStore.getRelationshipsByKey(2) == std::unordered_set<int>{6, 10});
        REQUIRE(affectsStore.getRelationshipsByKey(4) == std::unordered_set<int>{4, 8, 10, 12});
        REQUIRE(affectsStore.getRelationshipsByKey(6) == std::unordered_set<int>{6, 10});
        REQUIRE(affectsStore.getRelationshipsByKey(8) == std::unordered_set<int>{10, 12});
        REQUIRE(affectsStore.getRelationshipsByKey(9) == std::unordered_set<int>{10});
        REQUIRE(affectsStore.getRelationshipsByKey(10) == std::unordered_set<int>{11, 12});
        REQUIRE(affectsStore.getRelationshipsByKey(11) == std::unordered_set<int>{12});
	}
}