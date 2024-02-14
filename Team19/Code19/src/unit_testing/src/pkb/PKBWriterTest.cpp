//#include "catch.hpp"
//
//#include "pkb/PKB.h"
//#include "pkb/PKBReaderManager.h"
//#include "pkb/PKBWriterManager.h"
//
//TEST_CASE("pkb/PKBWriterManager.h") {
//  std::shared_ptr<PKB> pkb = std::make_shared<PKB>();
//  std::shared_ptr<PKBReaderManager> pkbReader = std::make_shared<PKBReaderManager>(pkb);
//  std::shared_ptr<PKBWriterManager> pkbWriter = std::make_shared<PKBWriterManager>(pkb);
//
//  SECTION("insertVariable: Basic") {
//    std::string x = "x";
//    pkbWriter->insertVariable(x);
//    std::unordered_set<std::string> variables = pkbReader->getAllVariables();
//    REQUIRE(variables.size() == 1);
//    REQUIRE(variables.find(x) != variables.end());
//  }
//
//    SECTION("insertVariable: Multiple") {
//        std::string x = "x";
//        std::string y = "y";
//        pkbWriter->insertVariable(x);
//        pkbWriter->insertVariable(y);
//        std::unordered_set<std::string> variables = pkbReader->getAllVariables();
//        REQUIRE(variables.size() == 2);
//        REQUIRE(variables.find(x) != variables.end());
//        REQUIRE(variables.find(y) != variables.end());
//    }
//
//    SECTION("insertVariable: Duplicate") {
//        std::string x = "x";
//        pkbWriter->insertVariable(x);
//        pkbWriter->insertVariable(x);
//        std::unordered_set<std::string> variables = pkbReader->getAllVariables();
//        REQUIRE(variables.size() == 1);
//        REQUIRE(variables.find(x) != variables.end());
//    }
//}
