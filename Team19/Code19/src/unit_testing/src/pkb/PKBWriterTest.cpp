#include "catch.hpp"

#include "pkb/PKB.h"
#include "pkb/PKBReader.h"
#include "pkb/PKBWriter.h"

TEST_CASE("pkb/PKBWriter.h") {
  std::shared_ptr<PKB> pkb = std::make_shared<PKB>();
  std::shared_ptr<PKBReader> pkbReader = std::make_shared<PKBReader>(pkb);
  std::shared_ptr<PKBWriter> pkbWriter = std::make_shared<PKBWriter>(pkb);

  SECTION("insertVariable: Basic") {
    std::string x = "x";
    pkbWriter->insertVariable(x);
    std::unordered_set<std::string> variables = pkbReader->getAllVariables();
    REQUIRE(variables.size() == 1);
    REQUIRE(variables.find(x) != variables.end());
  }

    SECTION("insertVariable: Multiple") {
        std::string x = "x";
        std::string y = "y";
        pkbWriter->insertVariable(x);
        pkbWriter->insertVariable(y);
        std::unordered_set<std::string> variables = pkbReader->getAllVariables();
        REQUIRE(variables.size() == 2);
        REQUIRE(variables.find(x) != variables.end());
        REQUIRE(variables.find(y) != variables.end());
    }

    SECTION("insertVariable: Duplicate") {
        std::string x = "x";
        pkbWriter->insertVariable(x);
        pkbWriter->insertVariable(x);
        std::unordered_set<std::string> variables = pkbReader->getAllVariables();
        REQUIRE(variables.size() == 1);
        REQUIRE(variables.find(x) != variables.end());
    }
}
