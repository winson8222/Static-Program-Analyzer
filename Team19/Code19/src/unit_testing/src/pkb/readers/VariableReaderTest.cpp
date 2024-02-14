#include "catch.hpp"
#include "pkb/PKBManager.h"

TEST_CASE("pkb/readers/VariableReader") {
  std::string x = "x";
  std::string y = "y";
  auto pkbManager = std::make_shared<PKBManager>();
  auto pkbReader = pkbManager->getPKBReaderManager();
  auto pkbWriter = pkbManager->getPKBWriterManager();
  auto variableReader = pkbReader->getVariableReader();
  auto variableWriter = pkbWriter->getVariableWriter();

  SECTION("getAllVariables: Empty") {
    REQUIRE(variableReader->getAllVariables().empty());
  }

  SECTION("getAllVariables: Non-empty") {
    variableWriter->insertVariable(x);
    variableWriter->insertVariable(y);
    REQUIRE(variableReader->getAllVariables() == std::unordered_set<std::string>{"x", "y"});
    variableWriter->clear();
  }
}