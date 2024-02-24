#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: ConstantReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    // Use ConstantWriter to directly populate constants
    auto constantWriter = pkbManager->getPKBWriterManager()->getConstantWriter();

    // Clearing the store before populating it to ensure a clean state
    constantWriter->clear();

    // Directly populating some constants for retrieval tests
    constantWriter->insertConstant(1);
    constantWriter->insertConstant(2);
    constantWriter->insertConstant(6);
    constantWriter->insertConstant(1010010101);
    constantWriter->insertConstant(3);
    constantWriter->insertConstant(4);

    auto constantReader = pkbManager->getPKBReaderManager()->getConstantReader();

    SECTION("Verify retrieval of all constants") {
        std::unordered_set<int> expectedConstants = {1, 2, 6, 1010010101, 3, 4};
        auto retrievedConstants = constantReader->getAllConstants();
        REQUIRE(retrievedConstants == expectedConstants);
    }

    SECTION("Check specific constants exist") {
        REQUIRE(constantReader->hasConstant(1) == true);
        REQUIRE(constantReader->hasConstant(6) == true);
        REQUIRE(constantReader->hasConstant(1010010101) == true);
        REQUIRE(constantReader->hasConstant(999) == false); // Verify a non-existent constant
    }

    SECTION("Check if ConstantStore is empty") {
        REQUIRE(constantReader->isEmpty() == false);
    }

    SECTION("Test Duplicate Constants") {
        constantWriter->clear(); // Reset for a clean state
        constantWriter->insertConstant(5);
        constantWriter->insertConstant(5); // Insert duplicate
        auto constants = constantReader->getAllConstants();
        // Depending on system behavior, adjust the expectation accordingly
        REQUIRE(constants.size() == 1);
        REQUIRE(constants.count(5) == 1);
    }

    SECTION("Performance Test for Large Number of Constants") {
        constantWriter->clear(); // Reset for a clean state
        for(int i = 0; i < 10000; ++i) {
            constantWriter->insertConstant(i);
        }
        // No specific REQUIRE statement; this section is for performance measurement
    }

    SECTION("Test Range of Constants") {
        constantWriter->clear(); // Reset for a clean state
        constantWriter->insertConstant(INT_MIN);
        constantWriter->insertConstant(-1);
        constantWriter->insertConstant(0);
        constantWriter->insertConstant(INT_MAX);

        REQUIRE(constantReader->hasConstant(INT_MIN) == true);
        REQUIRE(constantReader->hasConstant(-1) == true);
        REQUIRE(constantReader->hasConstant(0) == true);
        REQUIRE(constantReader->hasConstant(INT_MAX) == true);
    }


    // The clear method at the end is optional and depends on whether we want to clean the state after tests
    // constantWriter->clear();
}
