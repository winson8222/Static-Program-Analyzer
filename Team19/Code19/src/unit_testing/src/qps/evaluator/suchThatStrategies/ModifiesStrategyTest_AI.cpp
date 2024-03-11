
#include "catch.hpp"
#include "qps/evaluator/suchThatStrategies/ModifiesStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "../../spa/src/qps/parser/QueryParser.h"
#include "../../spa/src/pkb/PKBManager.h"
#include "../../spa/src/qps/evaluator/QueryEvaluator.h"

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

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesStrategy/1") {
    auto pkb = std::make_shared<PKB>();
    // Setup PKB with Modifies relationships
    pkb->getModifiesPStore()->addRelationship("procedure1", "x");
    pkb->getModifiesSStore()->addRelationship(2, "y");

    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    ModifiesStrategy modifiesStrategy;

    SECTION("ModifiesS(2, y) is true") {
        auto parsingResult = createParsingResultForModifies("2", "y", false); // false indicates statement
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Assertions to verify the outcome for ModifiesS
        REQUIRE(resultTable->getRows().size() == 1); // Expecting exactly one row
        REQUIRE(resultTable->getRows()[0]["y"] == "y"); // Verifying the content of the row
    }

    SECTION("ModifiesS with non-existing statement number is false") {
        auto parsingResult = createParsingResultForModifies("999", "y", false); // false indicates statement
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Expectation: The result should indicate that the relationship does not exist
        REQUIRE(resultTable->getRows().empty());
    }

    SECTION("ModifiesS with wildcard for variable") {
        auto parsingResult = createParsingResultForModifies("2", "_", false); // Testing ModifiesS(2, _)
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Expectation: The result should indicate that statement 2 modifies any variable
        REQUIRE_FALSE(resultTable->getRows().empty()); // More specific checks can be added based on your implementation
    }

        // Test for modification in nested statements
    SECTION("ModifiesS in nested statements") {
        // Assuming statement 4 is a container statement that contains statement 2
        pkb->getModifiesSStore()->addRelationship(4, "x");
        auto parsingResult = createParsingResultForModifies("4", "x", false);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        REQUIRE_FALSE(resultTable->getRows().empty()); // Expecting the result to indicate modification
        // Additional specific checks as needed
    }
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesStrategy/2") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesSWriter> modifiesSWriter = pkbWriterManager->getModifiesSWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    modifiesSWriter->addModifiesS(2, "x");
    modifiesSWriter->addModifiesS(3, "y");

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Modifies, "Modifies"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Rparenthesis, ")")
    };

QueryParser parser(tokens);
auto parsingResult = parser.parse();
QueryEvaluator evaluator(pkbReaderManager, parsingResult);
std::unordered_set<string> res = evaluator.evaluateQuery();
REQUIRE(res == std::unordered_set<string>{ "2" });

}


TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesStrategy/3") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesSWriter> modifiesSWriter = pkbWriterManager->getModifiesSWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    modifiesSWriter->addModifiesS(2, "x");
    modifiesSWriter->addModifiesS(3, "y");

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Modifies, "Modifies"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Comma, ","),
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "SemanticError" });
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesStrategy/4") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesSWriter> modifiesSWriter = pkbWriterManager->getModifiesSWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    modifiesSWriter->addModifiesS(2, "x");
    modifiesSWriter->addModifiesS(3, "y");

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Modifies, "Modifies"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "2"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE((res == std::unordered_set<string>{ "1", "2", "3" } || res == std::unordered_set<string>{"2", "3", "1"} || res == std::unordered_set<string>{"3", "2", "1"}));
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesStrategy/5") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesSWriter> modifiesSWriter = pkbWriterManager->getModifiesSWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addModifiesS(2, "x");
    modifiesSWriter->addModifiesS(3, "y");
    modifiesSWriter->addModifiesS(4, "z");

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "variable"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Modifies, "Modifies"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "3"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"y"});
}

TEST_CASE("ModifiesP Strategy - Evaluating procedure-variable modification relationships") {
    auto pkb = std::make_shared<PKB>();
    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
    // Assume ModifiesP relationships are added to PKB
    pkb->getModifiesPStore()->addRelationship("UpdateScore", "score");
    pkb->getModifiesPStore()->addRelationship("ResetGame", "gameState");
    pkb->getModifiesPStore()->addRelationship("LoadSettings", "volume");
    pkb->getCallsStore()->addRelationship("Main", "UpdateScore");
    pkb->getCallsStore()->addRelationship("Main", "ResetGame");

    ModifiesStrategy modifiesStrategy;

    SECTION("ModifiesP for specific procedure and variable") {
        auto parsingResult = createParsingResultForModifies("UpdateScore", "score", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        REQUIRE(resultTable->getRows().size() == 1); // Expecting a match
    }

    SECTION("ModifiesP for procedure with wildcard variable") {
        auto parsingResult = createParsingResultForModifies("ResetGame", "_", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        REQUIRE_FALSE(resultTable->getRows().empty()); // Expecting a match as ResetGame modifies any variable
    }

    SECTION("ModifiesP for wildcard procedure and specific variable") {
        auto parsingResult = createParsingResultForModifies("_", "volume", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        REQUIRE(resultTable->getRows().size() == 1); // Expecting a match for LoadSettings
    }

    SECTION("ModifiesP with non-existing procedure") {
        auto parsingResult = createParsingResultForModifies("NonExistentProc", "score", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        REQUIRE(resultTable->getRows().empty()); // No match expected
    }

    SECTION("ModifiesP with non-existing variable") {
        auto parsingResult = createParsingResultForModifies("UpdateScore", "nonExistentVar", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        REQUIRE(resultTable->getRows().empty()); // No match expected
    }

    SECTION("ModifiesP through indirect procedure call") {
        auto parsingResult = createParsingResultForModifies("Main", "score", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Expecting a match since Main indirectly modifies "score" through UpdateScore
        REQUIRE(resultTable->getRows().size() == 1);
    }

    SECTION("ModifiesP with wildcard procedure and wildcard variable") {
        auto parsingResult = createParsingResultForModifies("_", "_", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Expecting matches since query checks if there are any modifications at all
        REQUIRE_FALSE(resultTable->getRows().empty());
    }

    SECTION("ModifiesP for procedure modifying multiple variables") {
        // Assuming 'MultiVarModProc' modifies both 'var1' and 'var2'
        pkb->getModifiesPStore()->addRelationship("MultiVarModProc", "var1");
        pkb->getModifiesPStore()->addRelationship("MultiVarModProc", "var2");
        auto parsingResult = createParsingResultForModifies("MultiVarModProc", "_", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Expecting matches for both variables modified by 'MultiVarModProc'
        REQUIRE(resultTable->getRows().size() >= 2);
    }

    SECTION("ModifiesP for specific variable modified by multiple procedures") {
        // Assuming both 'Proc1' and 'Proc2' modify 'sharedVar'
        pkb->getModifiesPStore()->addRelationship("Proc1", "sharedVar");
        pkb->getModifiesPStore()->addRelationship("Proc2", "sharedVar");
        auto parsingResult = createParsingResultForModifies("_", "sharedVar", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // Expecting matches for both 'Proc1' and 'Proc2'
        REQUIRE(resultTable->getRows().size() >= 2);
    }

    SECTION("ModifiesP with nested procedures not modifying any variable") {
        // Assuming 'EmptyProc' calls 'NestedEmptyProc' but neither modifies any variable
        pkb->getCallsStore()->addRelationship("EmptyProc", "NestedEmptyProc");
        auto parsingResult = createParsingResultForModifies("EmptyProc", "_", true);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
        // No modifications expected from 'EmptyProc' or its nested procedures
        REQUIRE(resultTable->getRows().empty());
    }
}

