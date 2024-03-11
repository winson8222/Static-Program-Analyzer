
#include "catch.hpp"
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesStrategy.h"
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesPStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"

// Helper function for creating a ParsingResult tailored for Modifies tests
ParsingResult createParsingResultForModifies(const std::string& entity, const std::string& variable, bool isProcedure) {
    ParsingResult parsingResult;
    // Set the entity type appropriately
    TokenType entityType = isProcedure ? TokenType::IDENT : TokenType::INTEGER;
    
    SuchThatClause clause;
    clause.setRelationship(Token(TokenType::ModifiesS, "Modifies"));
    clause.setFirstParam(Token(entityType, entity));
    clause.setSecondParam(Token(TokenType::IDENT, variable));
    parsingResult.addSuchThatClause(clause);
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
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        // Assertions to verify the outcome for ModifiesS
        REQUIRE(resultTable->getRows().size() == 1); // Expecting exactly one row
        REQUIRE(resultTable->getRows()[0]["y"] == "y"); // Verifying the content of the row
    }

    SECTION("ModifiesS with non-existing statement number is false") {
        auto parsingResult = createParsingResultForModifies("999", "y", false); // false indicates statement
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        // Expectation: The result should indicate that the relationship does not exist
        REQUIRE(resultTable->getRows().empty());
    }

    SECTION("ModifiesS with wildcard for variable") {
        auto parsingResult = createParsingResultForModifies("2", "_", false); // Testing ModifiesS(2, _)
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
        // Expectation: The result should indicate that statement 2 modifies any variable
        REQUIRE_FALSE(resultTable->getRows().empty()); // More specific checks can be added based on your implementation
    }

        // Test for modification in nested statements
    SECTION("ModifiesS in nested statements") {
        // Assuming statement 4 is a container statement that contains statement 2
        pkb->getModifiesSStore()->addRelationship(4, "x");
        auto parsingResult = createParsingResultForModifies("4", "x", false);
        auto resultTable = modifiesStrategy.evaluateQuery(*pkbReaderManager, parsingResult, parsingResult.getSuchThatClauses()[0]);
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



TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesStrategy/6") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesSWriter> modifiesSWriter = pkbWriterManager->getModifiesSWriter();
    auto assignWriter = pkbWriterManager->getAssignWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addModifiesS(2, "x");
    modifiesSWriter->addModifiesS(3, "y");
    modifiesSWriter->addModifiesS(4, "z");
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);
    assignWriter->insertAssign(4);

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "variable"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::LeftAngleBracket, "<"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::RightAngleBracket, ">"),
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
    REQUIRE(res == std::unordered_set<string>{ "y", "1 2 3 4", "2 3 4" });
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/ModifiesStrategy/7") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesSWriter> modifiesSWriter = pkbWriterManager->getModifiesSWriter();
    auto assignWriter = pkbWriterManager->getAssignWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addModifiesS(2, "x");
    modifiesSWriter->addModifiesS(3, "y");
    modifiesSWriter->addModifiesS(4, "z");
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);
    assignWriter->insertAssign(4);

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "variable"),
            Token(TokenType::IDENT, "v1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "v2"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::LeftAngleBracket, "<"),
            Token(TokenType::IDENT, "v1"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "v2"),
            Token(TokenType::RightAngleBracket, ">"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Modifies, "Modifies"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "3"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "v1"),
            Token(TokenType::Rparenthesis, ")"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Modifies, "Modifies"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::INTEGER, "4"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "v2"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"y", "z", "3", "2", "4"});
}