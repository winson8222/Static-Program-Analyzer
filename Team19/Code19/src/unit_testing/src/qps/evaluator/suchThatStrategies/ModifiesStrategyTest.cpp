
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

//TEST_CASE("ModifiesStrategy Evaluation for ModifiesP and ModifiesS", "[Modifies]") {
//    auto pkb = std::make_shared<PKB>();
//    // Setup PKB with Modifies relationships
//    pkb->getModifiesPStore()->addRelationship("procedure1", "x");
//    pkb->getModifiesSStore()->addRelationship(2, "y");
//
//    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
//    ModifiesStrategy modifiesStrategy;
//
//    SECTION("ModifiesP(procedure1, x) is true") {
//        auto parsingResult = createParsingResultForModifies("procedure1", "x", true); // true indicates procedure
//        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        // Assertions to verify the outcome for ModifiesP
//    }
//
//    SECTION("ModifiesS(2, y) is true") {
//        auto parsingResult = createParsingResultForModifies("2", "y", false); // false indicates statement
//        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        // Assertions to verify the outcome for ModifiesS
//    }
//
//    SECTION("ModifiesP with non-existing procedure is false") {
//        auto parsingResult = createParsingResultForModifies("nonExistingProcedure", "x", true); // true indicates procedure
//        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        // Expectation: The result should indicate that the relationship does not exist
//        REQUIRE(resultTable->getRows().empty());
//    }
//
//    SECTION("ModifiesS with non-existing statement number is false") {
//        auto parsingResult = createParsingResultForModifies("999", "y", false); // false indicates statement
//        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        // Expectation: The result should indicate that the relationship does not exist
//        REQUIRE(resultTable->getRows().empty());
//    }
//
//    SECTION("ModifiesP where procedure does not modify the variable") {
//        auto parsingResult = createParsingResultForModifies("procedure1", "nonModifiedVar", true);
//        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        // Assertions to verify the procedure does not modify the variable
//        REQUIRE(resultTable->getRows().empty());
//    }
//
//    SECTION("ModifiesS where statement does not modify the variable") {
//        auto parsingResult = createParsingResultForModifies("2", "nonModifiedVar", false);
//        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        // Assertions to verify the statement does not modify the variable
//        REQUIRE(resultTable->getRows().empty());
//    }
//
//    SECTION("ModifiesS with wildcard for variable") {
//        auto parsingResult = createParsingResultForModifies("2", "_", false); // Testing ModifiesS(2, _)
//        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        // Expectation: The result should indicate that statement 2 modifies any variable
//        REQUIRE_FALSE(resultTable->getRows().empty());
//    }
//
//    SECTION("ModifiesP with wildcard for variable") {
//        auto parsingResult = createParsingResultForModifies("procedure1", "_", true); // Testing ModifiesP(procedure1, _)
//        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        // Expectation: The result should indicate that the procedure modifies any variable
//        REQUIRE_FALSE(resultTable->getRows().empty());
//    }
//
//
//    // Test for modification in nested statements
//    SECTION("ModifiesS in nested statements") {
//        // Assuming statement 4 is a container statement that contains statement 2
//        pkb->getModifiesSStore()->addRelationship(4, "x");
//        auto parsingResult = createParsingResultForModifies("4", "x", false);
//        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        REQUIRE_FALSE(resultTable->getRows().empty()); // Expecting the result to indicate modification
//    }
//
//    // Test for wildcard entity with specific variable
//    SECTION("ModifiesS with wildcard entity and specific variable") {
//        auto parsingResult = createParsingResultForModifies("_", "x", false); // Using wildcard for statement
//        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        REQUIRE_FALSE(resultTable->getRows().empty()); // Expecting at least one statement modifies 'x'
//    }
//
//}

TEST_CASE("Check Evaluation result of a simple select v for ModifiesS") {
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


TEST_CASE("Check Evaluation result of a simple select all s given true condition for ModifiesS") {
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
    REQUIRE((res == std::unordered_set<string>{ "1", "2", "3" } || res == std::unordered_set<string>{"2", "3", "1"} || res == std::unordered_set<string>{"3", "2", "1"}));
}





TEST_CASE("Check Evaluation result of a simple select all s given true condition for ModifiesS (opposite)") {
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


TEST_CASE("Check Evaluation result of a simple select variable given LHS for ModifiesS") {
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
