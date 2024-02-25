
#include "catch.hpp"
#include "qps/evaluator/suchThatStrategies/FollowsStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"

ParsingResult createParsingResultForFollows(int stmt1, int stmt2, bool isTransitive = false) {
    ParsingResult parsingResult;
    TokenType relationshipType = isTransitive ? TokenType::FollowsT : TokenType::Follows;
    parsingResult.setSuchThatClauseRelationship(Token(relationshipType, ""));
    parsingResult.setSuchThatClauseFirstParam(Token(TokenType::INTEGER, std::to_string(stmt1)));
    parsingResult.setSuchThatClauseSecondParam(Token(TokenType::INTEGER, std::to_string(stmt2)));
    return parsingResult;
}

TEST_CASE("FollowsStrategy Evaluation for Follows and FollowsT", "[Follows]") {
    auto pkb = std::make_shared<PKB>();
    auto followsStore = pkb->getFollowsStore();
    followsStore->addRelationship(1, 2);
    followsStore->addRelationship(2, 3);
    followsStore->addRelationship(3, 4); // Added for transitive testing

    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    FollowsStrategy followsStrategy;

    SECTION("Direct Follows(1, 2) is true") {
        auto parsingResult1 = createParsingResultForFollows(1, 2);
        auto resultTable = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult1);
        // Verify result for Follows(1, 2)
    }

    SECTION("Direct Follows(2, 3) is true") {
        auto parsingResult2 = createParsingResultForFollows(2, 3);
        auto resultTable = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult2);
        // Verify result for Follows(2, 3)
    }

    SECTION("Transitive Follows*(1, 3) is true") {
        auto parsingResult3 = createParsingResultForFollows(1, 3, true);
        auto resultTable = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult3);
        // Verify result for Follows*(1, 3)
    }

    SECTION("Transitive Follows*(1, 4) is true") {
        auto parsingResult4 = createParsingResultForFollows(1, 4, true);
        auto resultTable = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult4);
        // Verify result for Follows*(1, 4)
    }

    SECTION("Transitive Follows*(1, 5) is false") {
        auto parsingResult5 = createParsingResultForFollows(1, 5, true);
        auto resultTable = followsStrategy.evaluateQuery(*pkbReaderManager, parsingResult5);
        // Verify result for Follows*(1, 5) is correctly handled
    }
}
