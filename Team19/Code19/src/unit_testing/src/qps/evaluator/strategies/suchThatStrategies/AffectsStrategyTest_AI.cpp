#include "catch.hpp"
#include "qps/evaluator/strategies/suchThatStrategies/AffectsStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"

TEST_CASE("src/qps/evaluator/suchThatStrategies/AffectsStrategy/1") {
std::shared_ptr <PKBManager> pkbManager = std::make_shared<PKBManager>();
std::shared_ptr <PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
std::shared_ptr <PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
std::shared_ptr <AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
std::shared_ptr <AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
std::shared_ptr <ModifiesSWriter> modifiesSWriter = pkbWriterManager->getModifiesSWriter();
std::shared_ptr <ModifiesPWriter> modifiesPWriter = pkbWriterManager->getModifiesPWriter();
std::shared_ptr <NextWriter> nextWriter = pkbWriterManager->getNextWriter();
std::shared_ptr <UsesSWriter> usesSWriter = pkbWriterManager->getUsesSWriter();
std::shared_ptr <StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
std::shared_ptr <VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
std::shared_ptr <PrintWriter> printWriter = pkbWriterManager->getPrintWriter();
std::shared_ptr <PrintVarNameWriter> printVarNameWriter = pkbWriterManager->getPrintVarNameWriter();


statementWriter->insertStatement(1);
statementWriter->insertStatement(2);
statementWriter->insertStatement(3);
statementWriter->insertStatement(4);
statementWriter->insertStatement(5);
statementWriter->insertStatement(6);
assignWriter->insertAssign(1);
assignWriter->insertAssign(2);
assignWriter->insertAssign(3);
assignWriter->insertAssign(4);
modifiesSWriter->addModifiesS(1, "x");
modifiesSWriter->addModifiesS(2, "y");
modifiesSWriter->addModifiesS(3, "z");
modifiesSWriter->addModifiesS(4, "x");
usesSWriter->addUsesS(1, "y");
usesSWriter->addUsesS(2, "z");
usesSWriter->addUsesS(2, "x");
usesSWriter->addUsesS(3, "x");
usesSWriter->addUsesS(3, "z");
usesSWriter->addUsesS(4, "x");
usesSWriter->addUsesS(4, "y");
nextWriter->addNext(1, 2);
nextWriter->addNext(2, 3);
nextWriter->addNext(3, 4);
nextWriter->addNext(4, 5);
nextWriter->addNext(5, 6);
variableWriter->insertVariable("x");
variableWriter->insertVariable("y");
variableWriter->insertVariable("z");
printWriter->insertPrint(6);
printVarNameWriter->addPrintVarName(6, "x");
usesSWriter->addUsesS(6, "x");
assignPatternWriter->addAssignPattern(1, "x", "'y''1''+'");
assignPatternWriter->addAssignPattern(2, "y", "'z''x''+'");
assignPatternWriter->addAssignPattern(3, "z", "'x''z''+'");
assignPatternWriter->addAssignPattern(4, "x", "'x''y''+'");
pkbManager->getPKBCacheManager()->populateCache();

SECTION("AffectsStrategy/Verify Direct Affects Relationship") {
// Define tokens for the query
std::vector <Token> tokens = {
        Token(TokenType::SelectKeyword, "Select"),
        Token(TokenType::BooleanKeyword, "BOOLEAN"),
        Token(TokenType::SuchKeyword, "such"),
        Token(TokenType::ThatKeyword, "that"),
        Token(TokenType::Affects, "Affects"),
        Token(TokenType::Lparenthesis, "("),
        Token(TokenType::INTEGER, "2"),
        Token(TokenType::Comma, ","),
        Token(TokenType::INTEGER, "3"),
        Token(TokenType::Rparenthesis, ")")
};

QueryParser parser(tokens);
auto parsingResult = parser.parse();
QueryEvaluator evaluator(pkbReaderManager, parsingResult);
std::unordered_set <string> res = evaluator.evaluateQuery();
REQUIRE(res
== std::unordered_set <string>{
"FALSE"}); // Expect TRUE as 2 Affects 3 is defined
}

SECTION("AffectsStrategy/Verify Affects Relationship") {


// Define tokens for the query testing transitive relationship
std::vector <Token> tokens = {
        Token(TokenType::SelectKeyword, "Select"),
        Token(TokenType::BooleanKeyword, "BOOLEAN"),
        Token(TokenType::SuchKeyword, "such"),
        Token(TokenType::ThatKeyword, "that"),
        Token(TokenType::Affects, "Affects"),
        Token(TokenType::Lparenthesis, "("),
        Token(TokenType::INTEGER, "1"),
        Token(TokenType::Comma, ","),
        Token(TokenType::INTEGER, "4"),
        Token(TokenType::Rparenthesis, ")")
};

QueryParser parser(tokens);
auto parsingResult = parser.parse();
QueryEvaluator evaluator(pkbReaderManager, parsingResult);
std::unordered_set <string> res = evaluator.evaluateQuery();
REQUIRE(res
== std::unordered_set <string>{
"TRUE"});
}

SECTION("AffectsStrategy/Verify Affects Relationship with 1 Int and 1 IDENT (FALSE)") {

// Define tokens for the query testing transitive relationship


std::vector <Token> tokens = {
        Token(TokenType::DesignEntity, "stmt"),
        Token(TokenType::IDENT, "s"),
        Token(TokenType::Semicolon, ";"),
        Token(TokenType::SelectKeyword, "Select"),
        Token(TokenType::BooleanKeyword, "BOOLEAN"),
        Token(TokenType::SuchKeyword, "such"),
        Token(TokenType::ThatKeyword, "that"),
        Token(TokenType::Affects, "Affects"),
        Token(TokenType::Lparenthesis, "("),
        Token(TokenType::IDENT, "s"),
        Token(TokenType::Comma, ","),
        Token(TokenType::INTEGER, "1"),
        Token(TokenType::Rparenthesis, ")")
};

QueryParser parser(tokens);
auto parsingResult = parser.parse();
QueryEvaluator evaluator(pkbReaderManager, parsingResult);
std::unordered_set <string> res = evaluator.evaluateQuery();
REQUIRE(res
== std::unordered_set <string>{
"FALSE"});
}

SECTION("AffectsStrategy/Verify Affects Relationship with 1 Int and 1 IDENT (TRUE)") {


// Define tokens for the query testing transitive relationship
std::vector <Token> tokens = {
        Token(TokenType::DesignEntity, "stmt"),
        Token(TokenType::IDENT, "s"),
        Token(TokenType::Semicolon, ";"),
        Token(TokenType::SelectKeyword, "Select"),
        Token(TokenType::BooleanKeyword, "BOOLEAN"),
        Token(TokenType::SuchKeyword, "such"),
        Token(TokenType::ThatKeyword, "that"),
        Token(TokenType::Affects, "Affects"),
        Token(TokenType::Lparenthesis, "("),
        Token(TokenType::IDENT, "s"),
        Token(TokenType::Comma, ","),
        Token(TokenType::INTEGER, "3"),
        Token(TokenType::Rparenthesis, ")")
};

QueryParser parser(tokens);
auto parsingResult = parser.parse();
QueryEvaluator evaluator(pkbReaderManager, parsingResult);
std::unordered_set <string> res = evaluator.evaluateQuery();
REQUIRE(res
== std::unordered_set <string>{
"TRUE"});
}

SECTION("Select stmt from AffectsT Relationship") {


// Define tokens for the query testing transitive relationship
std::vector <Token> tokens = {
        Token(TokenType::DesignEntity, "stmt"),
        Token(TokenType::IDENT, "s"),
        Token(TokenType::Semicolon, ";"),
        Token(TokenType::SelectKeyword, "Select"),
        Token(TokenType::IDENT, "s"),
        Token(TokenType::SuchKeyword, "such"),
        Token(TokenType::ThatKeyword, "that"),
        Token(TokenType::Affects, "Affects"),
        Token(TokenType::Lparenthesis, "("),
        Token(TokenType::IDENT, "s"),
        Token(TokenType::Comma, ","),
        Token(TokenType::INTEGER, "4"),
        Token(TokenType::Rparenthesis, ")")
};

QueryParser parser(tokens);
auto parsingResult = parser.parse();
QueryEvaluator evaluator(pkbReaderManager, parsingResult);
std::unordered_set <string> res = evaluator.evaluateQuery();
REQUIRE(res
== std::unordered_set <string>{
"2", "1"});
}

SECTION("Select stmt from Affects Relationship with 1 Int and 1 IDENT") {


// Define tokens for the query testing transitive relationship
std::vector <Token> tokens = {
        Token(TokenType::DesignEntity, "assign"),
        Token(TokenType::IDENT, "a"),
        Token(TokenType::Semicolon, ";"),
        Token(TokenType::SelectKeyword, "Select"),
        Token(TokenType::IDENT, "a"),
        Token(TokenType::SuchKeyword, "such"),
        Token(TokenType::ThatKeyword, "that"),
        Token(TokenType::Affects, "Affects"),
        Token(TokenType::Lparenthesis, "("),
        Token(TokenType::IDENT, "a"),
        Token(TokenType::Comma, ","),
        Token(TokenType::INTEGER, "4"),
        Token(TokenType::Rparenthesis, ")")
};

QueryParser parser(tokens);
auto parsingResult = parser.parse();
QueryEvaluator evaluator(pkbReaderManager, parsingResult);
std::unordered_set <string> res = evaluator.evaluateQuery();
REQUIRE(res
== std::unordered_set <string>{
"2", "1"});
}

    SECTION("Select all affected stmt") {

    string query = "stmt s; Select s such that Affects(_, s)";
    Tokenizer tokenizer(query);
    auto tokens = tokenizer.tokenize();
// Define tokens for the query testing transitive relationship
//        std::vector <Token> tokens = {
//                Token(TokenType::DesignEntity, "stmt"),
//                Token(TokenType::IDENT, "s"),
//                Token(TokenType::Semicolon, ";"),
//                Token(TokenType::SelectKeyword, "Select"),
//                Token(TokenType::IDENT, "s"),
//                Token(TokenType::SuchKeyword, "such"),
//                Token(TokenType::ThatKeyword, "that"),
//                Token(TokenType::Affects, "Affects"),
//                Token(TokenType::Lparenthesis, "("),
//                Token(TokenType::Wildcard, "_"),
//                Token(TokenType::Comma, ","),
//                Token(TokenType::IDENT, "s"),
//                Token(TokenType::Rparenthesis, ")")
//        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set <string> res = evaluator.evaluateQuery();
        REQUIRE(res
                == std::unordered_set <string>{
                "2", "4", "3"});
    }

    SECTION("Select all affected stmt") {

        string query = "stmt s; Select s such that Affects(s, _)";
        Tokenizer tokenizer(query);
        auto tokens = tokenizer.tokenize();
// Define tokens for the query testing transitive relationship
//        std::vector <Token> tokens = {
//                Token(TokenType::DesignEntity, "stmt"),
//                Token(TokenType::IDENT, "s"),
//                Token(TokenType::Semicolon, ";"),
//                Token(TokenType::SelectKeyword, "Select"),
//                Token(TokenType::IDENT, "s"),
//                Token(TokenType::SuchKeyword, "such"),
//                Token(TokenType::ThatKeyword, "that"),
//                Token(TokenType::Affects, "Affects"),
//                Token(TokenType::Lparenthesis, "("),
//                Token(TokenType::IDENT, "s"),
//                Token(TokenType::Comma, ","),
//                Token(TokenType::Wildcard, "_"),
//                Token(TokenType::Rparenthesis, ")")
//        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set <string> res = evaluator.evaluateQuery();
        REQUIRE(res
                == std::unordered_set <string>{
                "2", "1"});
    }
    SECTION("Select stmt affecting print") {

        string query = "stmt s; print p; Select s such that Affects(s, p)";
        Tokenizer tokenizer(query);
        auto tokens = tokenizer.tokenize();
// Define tokens for the query testing transitive relationship
//        std::vector <Token> tokens = {
//                Token(TokenType::DesignEntity, "stmt"),
//                Token(TokenType::IDENT, "s"),
//                Token(TokenType::Semicolon, ";"),
//                Token(TokenType::SelectKeyword, "Select"),
//                Token(TokenType::IDENT, "s"),
//                Token(TokenType::SuchKeyword, "such"),
//                Token(TokenType::ThatKeyword, "that"),
//                Token(TokenType::Affects, "Affects"),
//                Token(TokenType::Lparenthesis, "("),
//                Token(TokenType::IDENT, "s"),
//                Token(TokenType::Comma, ","),
//                Token(TokenType::Wildcard, "_"),
//                Token(TokenType::Rparenthesis, ")")
//        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set <string> res = evaluator.evaluateQuery();
//        REQUIRE(res
//                == std::unordered_set <string>{
//                "4", "1"});
    }
}

