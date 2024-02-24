#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: VariableReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto variableWriter = pkbManager->getPKBWriterManager()->getVariableWriter();

    // Clearing the store before populating it to ensure a clean state
    variableWriter->clear();

    // Populating some variables for retrieval tests
    std::string varX = "x";
    std::string varY = "y";
    std::string varZ = "z";
    std::string varRead = "read"; // Example of a keyword as a variable name
    variableWriter->insertVariable(varX);
    variableWriter->insertVariable(varY);
    variableWriter->insertVariable(varZ);
    variableWriter->insertVariable(varRead);

    auto variableReader = pkbManager->getPKBReaderManager()->getVariableReader();

    SECTION("Verify retrieval of all variables") {
        std::unordered_set<std::string> expectedVariables = {varX, varY, varZ, varRead};
        auto retrievedVariables = variableReader->getAllVariables();
        REQUIRE(retrievedVariables == expectedVariables);
    }

    SECTION("Check specific variables exist") {
        REQUIRE(variableReader->hasVariable(varX) == true);
        REQUIRE(variableReader->hasVariable(varY) == true);
        REQUIRE(variableReader->hasVariable("nonExistentVar") == false); // Test for a variable that doesn't exist
    }

    SECTION("Check if VariableStore is empty") {
        REQUIRE(variableReader->isEmpty() == false);
    }

    SECTION("Test for variable naming conventions") {
        std::string longName = "x" + std::string(100, 'i'); // Assuming a very long variable name
        std::string specialCharName = "var$special";
        std::string keywordLikeName = "whileVar"; // Resembles a keyword

        variableWriter->insertVariable(longName);
        variableWriter->insertVariable(specialCharName);
        variableWriter->insertVariable(keywordLikeName);

        REQUIRE(variableReader->hasVariable(longName) == true);
        REQUIRE(variableReader->hasVariable(specialCharName) == true);
        REQUIRE(variableReader->hasVariable(keywordLikeName) == true);
    }

    SECTION("Test for case sensitivity") {
        std::string lowerCase = "case";
        std::string upperCase = "CASE";

        variableWriter->insertVariable(lowerCase);
        variableWriter->insertVariable(upperCase);

        REQUIRE(variableReader->hasVariable(lowerCase) == true);
        REQUIRE(variableReader->hasVariable(upperCase) == true);
        REQUIRE(lowerCase != upperCase); // Ensure case sensitivity is respected
    }

    SECTION("Test for variables with similar names") {
        std::string name1 = "part";
        std::string name2 = "partOne";
        std::string name3 = "partTwo";

        variableWriter->insertVariable(name1);
        variableWriter->insertVariable(name2);
        variableWriter->insertVariable(name3);

        REQUIRE(variableReader->hasVariable(name1) == true);
        REQUIRE(variableReader->hasVariable(name2) == true);
        REQUIRE(variableReader->hasVariable(name3) == true);
    }

    SECTION("Test for handling invalid names") {
        std::string invalidName1 = "123abc"; // Assuming names cannot start with digits
        std::string invalidName2 = "@abc"; // Assuming names cannot start with special characters

        bool result1 = variableWriter->insertVariable(invalidName1);
        bool result2 = variableWriter->insertVariable(invalidName2);

        REQUIRE(result1 == false); // Assuming the insert operation returns false for invalid names
        REQUIRE(result2 == false);
        REQUIRE(variableReader->hasVariable(invalidName1) == false);
        REQUIRE(variableReader->hasVariable(invalidName2) == false);
    }


}
