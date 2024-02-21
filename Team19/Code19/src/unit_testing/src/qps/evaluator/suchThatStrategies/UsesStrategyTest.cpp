#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "qps/evaluator/suchThatStrategies/UsesStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/ParsingResult.h"

// Helper function for creating a ParsingResult tailored for Uses tests
ParsingResult createParsingResultForUses(const std::string& entity, const std::string& variable, bool isProcedure) {
    ParsingResult parsingResult;
    parsingResult.setSuchThatClauseRelationship(Token(TokenType::Uses, "Uses"));
    TokenType entityType = isProcedure ? TokenType::IDENT : TokenType::INTEGER;
    parsingResult.setSuchThatClauseFirstParam(Token(entityType, entity));
    parsingResult.setSuchThatClauseSecondParam(Token(TokenType::IDENT, variable));
    return parsingResult;
}

TEST_CASE("UsesStrategy Evaluation for UsesP and UsesS", "[Uses]") {
    auto pkb = std::make_shared<PKB>();
    // Setup PKB with Uses relationships
    pkb->getUsesPStore()->addRelationship("procedure1", "x");
    pkb->getUsesSStore()->addRelationship(2, "y");

    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    UsesStrategy usesStrategy;

    SECTION("UsesP(procedure1, x) is true") {
        auto parsingResult = createParsingResultForUses("procedure1", "x", true);
        auto resultTable = usesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Assertions to verify the outcome for UsesP
    }

    SECTION("UsesS(2, y) is true") {
        auto parsingResult = createParsingResultForUses("2", "y", false);
        auto resultTable = usesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Assertions to verify the outcome for UsesS
    }

    SECTION("UsesP(procedure1, y) is false") {
            auto parsingResult = createParsingResultForUses("procedure1", "y", true);
            auto resultTable = usesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
            // Assertions to verify the outcome for UsesP
        }

    // Test for usage in nested statements
    SECTION("UsesS in nested statements") {
        // Assuming statement 3 is a container statement that contains statement 2
        pkb->getUsesSStore()->addRelationship(3, "y");
        auto parsingResult = createParsingResultForUses("3", "y", false);
        auto resultTable = usesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        REQUIRE_FALSE(resultTable->getRows().empty()); // Expecting the result to indicate usage
    }

    // Test for wildcard entity with specific variable
    SECTION("UsesS with wildcard entity and specific variable") {
        auto parsingResult = createParsingResultForUses("_", "y", false); // Using wildcard for statement
        auto resultTable = usesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        REQUIRE_FALSE(resultTable->getRows().empty()); // Expecting at least one statement uses 'y'
    }

}
