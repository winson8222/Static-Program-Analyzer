#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "qps/evaluator/suchThatStrategies/ModifiesStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/ParsingResult.h"

// Helper function for creating a ParsingResult tailored for Modifies tests
ParsingResult createParsingResultForModifies(const std::string& entity, const std::string& variable, bool isProcedure) {
    ParsingResult parsingResult;
    parsingResult.setSuchThatClauseRelationship(Token(TokenType::Modifies, "Modifies"));
    // Set the entity type appropriately
    TokenType entityType = isProcedure ? TokenType::IDENT : TokenType::INTEGER;
    parsingResult.setSuchThatClauseFirstParam(Token(entityType, entity));
    parsingResult.setSuchThatClauseSecondParam(Token(TokenType::IDENT, variable));
    return parsingResult;
}

TEST_CASE("ModifiesStrategy Evaluation for ModifiesP and ModifiesS", "[Modifies]") {
    auto pkb = std::make_shared<PKB>();
    // Setup PKB with Modifies relationships
    pkb->getModifiesPStore()->addRelationship("procedure1", "x");
    pkb->getModifiesSStore()->addRelationship(2, "y");

    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    ModifiesStrategy modifiesStrategy;

    SECTION("ModifiesP(procedure1, x) is true") {
        auto parsingResult = createParsingResultForModifies("procedure1", "x", true); // true indicates procedure
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Assertions to verify the outcome for ModifiesP
    }

    SECTION("ModifiesS(2, y) is true") {
        auto parsingResult = createParsingResultForModifies("2", "y", false); // false indicates statement
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Assertions to verify the outcome for ModifiesS
    }

    SECTION("ModifiesP with non-existing procedure is false") {
        auto parsingResult = createParsingResultForModifies("nonExistingProcedure", "x", true); // true indicates procedure
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Expectation: The result should indicate that the relationship does not exist
        REQUIRE(resultTable->getRows().empty());
    }

    SECTION("ModifiesS with non-existing statement number is false") {
        auto parsingResult = createParsingResultForModifies("999", "y", false); // false indicates statement
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Expectation: The result should indicate that the relationship does not exist
        REQUIRE(resultTable->getRows().empty());
    }

    SECTION("ModifiesP where procedure does not modify the variable") {
        auto parsingResult = createParsingResultForModifies("procedure1", "nonModifiedVar", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Assertions to verify the procedure does not modify the variable
        REQUIRE(resultTable->getRows().empty());
    }

    SECTION("ModifiesS where statement does not modify the variable") {
        auto parsingResult = createParsingResultForModifies("2", "nonModifiedVar", false);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Assertions to verify the statement does not modify the variable
        REQUIRE(resultTable->getRows().empty());
    }

    SECTION("ModifiesS with wildcard for variable") {
        auto parsingResult = createParsingResultForModifies("2", "_", false); // Testing ModifiesS(2, _)
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Expectation: The result should indicate that statement 2 modifies any variable
        REQUIRE_FALSE(resultTable->getRows().empty());
    }

    SECTION("ModifiesP with wildcard for variable") {
        auto parsingResult = createParsingResultForModifies("procedure1", "_", true); // Testing ModifiesP(procedure1, _)
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Expectation: The result should indicate that the procedure modifies any variable
        REQUIRE_FALSE(resultTable->getRows().empty());
    }

}