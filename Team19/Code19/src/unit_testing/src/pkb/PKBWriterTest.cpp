#include "catch.hpp"

#include "pkb/PKB.h"
#include "pkb/PKBReader.h"
#include "pkb/PKBWriter.h"

TEST_CASE("pkb/PKBWriter.h") {
  shared_ptr<PKB> pkb = make_shared<PKB>();
  shared_ptr<PKBReader> pkbReader = make_shared<PKBReader>(pkb);
  shared_ptr<PKBWriter> pkbWriter = make_shared<PKBWriter>(pkb);

  SECTION("insertVariable: Basic") {
    string x = "x";
    pkbWriter->insertVariable(x);
    unordered_set<string> variables = pkbReader->getAllVariables();
    REQUIRE(variables.size() == 1);
    REQUIRE(variables.find(x) != variables.end());
  }

    SECTION("insertVariable: Multiple") {
        string x = "x";
        string y = "y";
        pkbWriter->insertVariable(x);
        pkbWriter->insertVariable(y);
        unordered_set<string> variables = pkbReader->getAllVariables();
        REQUIRE(variables.size() == 2);
        REQUIRE(variables.find(x) != variables.end());
        REQUIRE(variables.find(y) != variables.end());
    }

    SECTION("insertVariable: Duplicate") {
        string x = "x";
        pkbWriter->insertVariable(x);
        pkbWriter->insertVariable(x);
        unordered_set<string> variables = pkbReader->getAllVariables();
        REQUIRE(variables.size() == 1);
        REQUIRE(variables.find(x) != variables.end());
    }
}
