#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "qps/evaluator/suchThatStrategies/ParentStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/ParsingResult.h"
#include "qps/parser/Token.h"

ParsingResult createParsingResultForParent(int parentStmt, int childStmt, bool isTransitive = false) {
    ParsingResult parsingResult;
    TokenType relationshipType = isTransitive ? TokenType::ParentT : TokenType::Parent;
    parsingResult.setSuchThatClauseRelationship(Token(relationshipType, ""));
    parsingResult.setSuchThatClauseFirstParam(Token(TokenType::INTEGER, std::to_string(parentStmt)));
    parsingResult.setSuchThatClauseSecondParam(Token(TokenType::INTEGER, std::to_string(childStmt)));
    return parsingResult;
}

TEST_CASE("ParentStrategy Evaluation for Parent and ParentT", "[Parent]") {
    auto pkb = std::make_shared<PKB>();
    auto parentStore = pkb->getParentStore();
    parentStore->addRelationship(1, 2);
    parentStore->addRelationship(2, 3);
    parentStore->addRelationship(3, 4); // Added for Parent* (transitive) testing

    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    ParentStrategy parentStrategy;

    SECTION("Direct Parent(1, 2) is true") {
        auto parsingResult1 = createParsingResultForParent(1, 2);
        auto resultTable = parentStrategy.evaluateQuery(*pkbReaderManager, parsingResult1);
        // Verify result for Parent(1, 2)
    }

    SECTION("Direct Parent(2, 3) is true") {
        auto parsingResult2 = createParsingResultForParent(2, 3);
        auto resultTable = parentStrategy.evaluateQuery(*pkbReaderManager, parsingResult2);
        // Verify result for Parent(2, 3)
    }

    SECTION("Transitive Parent*(1, 3) is true") {
        auto parsingResult3 = createParsingResultForParent(1, 3, true);
        auto resultTable = parentStrategy.evaluateQuery(*pkbReaderManager, parsingResult3);
        // Verify result for Parent*(1, 3)
    }

    SECTION("Transitive Parent*(1, 4) is true") {
        auto parsingResult4 = createParsingResultForParent(1, 4, true);
        auto resultTable = parentStrategy.evaluateQuery(*pkbReaderManager, parsingResult4);
        // Verify result for Parent*(1, 4)
    }

    SECTION("Transitive Parent*(1, 5) is false") {
        auto parsingResult5 = createParsingResultForParent(1, 5, true);
        auto resultTable = parentStrategy.evaluateQuery(*pkbReaderManager, parsingResult5);
        // Verify result for Parent*(1, 5) is correctly handled
    }
}
