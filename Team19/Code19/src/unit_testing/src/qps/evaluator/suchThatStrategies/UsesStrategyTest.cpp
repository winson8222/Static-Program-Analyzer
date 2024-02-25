
#include "catch.hpp"
#include "qps/evaluator/suchThatStrategies/UsesStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "../../spa/src/qps/parser/QueryParser.h"
#include "../../spa/src/pkb/PKBManager.h"
#include "../../spa/src/qps/evaluator/QueryEvaluator.h"

// Helper function for creating a ParsingResult tailored for Uses tests
ParsingResult createParsingResultForUses(const std::string& entity, const std::string& variable, bool isProcedure) {
    ParsingResult parsingResult;
    parsingResult.setSuchThatClauseRelationship(Token(TokenType::Uses, "Uses"));
    TokenType entityType = isProcedure ? TokenType::IDENT : TokenType::INTEGER;
    parsingResult.setSuchThatClauseFirstParam(Token(entityType, entity));
    parsingResult.setSuchThatClauseSecondParam(Token(TokenType::IDENT, variable));
    return parsingResult;
}

//TEST_CASE("UsesStrategy Evaluation for UsesP and UsesS", "[Uses]") {
//    auto pkb = std::make_shared<PKB>();
//    // Setup PKB with Uses relationships
//    pkb->getUsesPStore()->addRelationship("procedure1", "x");
//    pkb->getUsesSStore()->addRelationship(2, "y");
//
//    auto pkbReaderManager = std::make_shared<PKBReaderManager>(pkb);
//    UsesStrategy usesStrategy;
//
//    SECTION("UsesP(procedure1, x) is true") {
//        auto parsingResult = createParsingResultForUses("procedure1", "x", true);
//        auto resultTable = usesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        // Assertions to verify the outcome for UsesP
//    }
//
//    SECTION("UsesS(2, y) is true") {
//        auto parsingResult = createParsingResultForUses("2", "y", false);
//        auto resultTable = usesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        // Assertions to verify the outcome for UsesS
//    }
//
//    SECTION("UsesP(procedure1, y) is false") {
//            auto parsingResult = createParsingResultForUses("procedure1", "y", true);
//            auto resultTable = usesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//            // Assertions to verify the outcome for UsesP
//        }
//
//    // Test for usage in nested statements
//    SECTION("UsesS in nested statements") {
//        // Assuming statement 3 is a container statement that contains statement 2
//        pkb->getUsesSStore()->addRelationship(3, "y");
//        auto parsingResult = createParsingResultForUses("3", "y", false);
//        auto resultTable = usesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        REQUIRE_FALSE(resultTable->getRows().empty()); // Expecting the result to indicate usage
//    }
//
//    // Test for wildcard entity with specific variable
//    SECTION("UsesS with wildcard entity and specific variable") {
//        auto parsingResult = createParsingResultForUses("_", "y", false); // Using wildcard for statement
//        auto resultTable = usesStrategy.evaluateQuery(*pkbReaderManager, parsingResult);
//        REQUIRE_FALSE(resultTable->getRows().empty()); // Expecting at least one statement uses 'y'
//    }
//
//}

TEST_CASE("Check Evaluation result of a simple select v for UseS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addUsesS(2, "x");
    modifiesSWriter->addUsesS(3, "y");
    modifiesSWriter->addUsesS(4, "z");


    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Uses, "Uses"),
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

TEST_CASE("Check Evaluation result of a simple select all s given true condition for UseS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addUsesS(2, "x");
    modifiesSWriter->addUsesS(3, "y");
    modifiesSWriter->addUsesS(4, "z");

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Uses, "Uses"),
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


TEST_CASE("Check Evaluation result of a simple select all s given true condition for UseS (opposite)") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addUsesS(2, "x");
    modifiesSWriter->addUsesS(3, "y");
    modifiesSWriter->addUsesS(4, "z");

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Uses, "Uses"),
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
    REQUIRE(res == std::unordered_set<string>{ "1", "2", "3", "4" });
}

TEST_CASE("Check Evaluation result of a simple select variable given LHS for UsesS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addUsesS(2, "x");
    modifiesSWriter->addUsesS(3, "y");
    modifiesSWriter->addUsesS(4, "z");


    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "variable"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Uses, "Uses"),
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


TEST_CASE("Check Evaluation result of 2 synonyms for UsesS and select statements") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addUsesS(2, "x");
    modifiesSWriter->addUsesS(3, "y");
    modifiesSWriter->addUsesS(4, "z");


    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "variable"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Uses, "Uses"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"x", "y", "z"});
}
