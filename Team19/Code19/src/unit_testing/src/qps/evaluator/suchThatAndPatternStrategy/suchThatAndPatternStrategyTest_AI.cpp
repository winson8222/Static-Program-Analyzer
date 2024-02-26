#include "catch.hpp"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"
#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"
// Including necessary headers for testing

// Test case for evaluating Parent* query with assignment pattern
TEST_CASE("src/qps/evaluator/suchThatAndPatternStrategy/suchThatAndPatternStrategy") {

    SECTION("Check Evaluation result of a simple select Parent* query ") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<ParentTWriter> parentTWriter = pkbWriterManager->getParentTWriter();
        std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
        std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
        std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();


        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        whileWriter->insertWhile(1);
        whileWriter->insertWhile(3);
        assignWriter->insertAssign(2);
        assignWriter->insertAssign(4);
        assignPatternWriter->addAssignPattern(2, "x", "1 + x");
        assignPatternWriter->addAssignPattern(4, "x", "2 + x");
        parentTWriter->addParentT(1, 2);
        parentTWriter->addParentT(3, 4);





        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "while"),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::QuoutConst, "\"1\""),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::ParentT, "Parent*"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Rparenthesis, ")")
        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{ "1" });

    }

    SECTION("Check Evaluation result of a simple select Parent* query + adding ifs ") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<ParentTWriter> parentTWriter = pkbWriterManager->getParentTWriter();
        std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
        std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
        std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
        std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();


        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        statementWriter->insertStatement(4);
        statementWriter->insertStatement(5);
        statementWriter->insertStatement(6);
        whileWriter->insertWhile(1);
        whileWriter->insertWhile(3);
        assignWriter->insertAssign(2);
        assignWriter->insertAssign(4);
        ifWriter->insertIf(5);
        assignPatternWriter->addAssignPattern(2, "x", "1 + x");
        assignPatternWriter->addAssignPattern(4, "x", "2 + x");
        assignPatternWriter->addAssignPattern(6, "x", "1 + x");
        parentTWriter->addParentT(1, 2);
        parentTWriter->addParentT(1, 6);
        parentTWriter->addParentT(3, 4);
        parentTWriter->addParentT(5,6);





        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "while"),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::ParentT, "Parent*"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::IDENT, "w"),
                Token(TokenType::Comma, ","),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Rparenthesis, ")"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Comma, ","),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::QuoutConst, "\"1\""),
                Token(TokenType::Wildcard, "_"),
                Token(TokenType::Rparenthesis, ")"),

        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{ "1" });

    }

    SECTION("Check Evaluation result of pattern and follows") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


        std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
        std::shared_ptr<FollowsWriter> followsWriter = pkbWriterManager->getFollowsWriter();
        std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
        std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();

        statementWriter->insertStatement(1);
        statementWriter->insertStatement(2);
        statementWriter->insertStatement(3);
        statementWriter->insertStatement(4);

        followsWriter->addFollows(1, 2);

        assignPatternWriter->addAssignPattern(1, "x", "1");
        assignPatternWriter->addAssignPattern(2, "x", "2");
        assignPatternWriter->addAssignPattern(3, "x", "3");

        assignWriter->insertAssign(1);
        assignWriter->insertAssign(2);
        assignWriter->insertAssign(3);



        std::vector<Token> tokens = {
                Token(TokenType::DesignEntity, "stmt"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::DesignEntity, "assign"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Semicolon, ";"),
                Token(TokenType::SelectKeyword, "Select"),
                Token(TokenType::IDENT, "s"),
                Token(TokenType::PatternKeyword, "pattern"),
                Token(TokenType::IDENT, "a"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::QuoutIDENT, "\"x\""),
                Token(TokenType::Comma, ","),
                Token(TokenType::QuoutConst, "\"1\""),
                Token(TokenType::Rparenthesis, ")"),
                Token(TokenType::SuchKeyword, "such"),
                Token(TokenType::ThatKeyword, "that"),
                Token(TokenType::Follows, "Follows"),
                Token(TokenType::Lparenthesis, "("),
                Token(TokenType::INTEGER, "1"),
                Token(TokenType::Comma, ","),
                Token(TokenType::INTEGER, "2"),
                Token(TokenType::Rparenthesis, ")"),


        };

        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator(pkbReaderManager, parsingResult);
        std::unordered_set<string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<string>{"1", "2", "3", "4"});
    }
}

TEST_CASE("Pattern partial match with semi-string") {

    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();

    std::string filename = "./sample.txt";
    std::string sampleProgram = "procedure proc1 {"
                                "   read x;"
                                "   while (y > 1) {"
                                "       y = y + 1; }" // 3
                                "   read x;"
                                "   while (y > 5) {"
                                "       z = z + 1; }}" // 6
                                "procedure proc2 {"
                                "   read x;"
                                "   while (y > 1) {"
                                "       y = y + 5; }" // 9
                                "   read x; "
                                "   y = 55;"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();



    REQUIRE(std::filesystem::exists(filename));
    SourceProcessor sp = SourceProcessor(filename, pkbManager);
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    assignPatternWriter->clear();

    sp.parseSIMPLE();
    sp.extractAndPopulate();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

    std::shared_ptr<AssignPatternReader> assignPatternReader = pkbReaderManager->getAssignPatternReader();
    std:shared_ptr<AssignReader> assignReader = pkbReaderManager->getAssignReader();
    std::unordered_set<int> shome = assignPatternReader->getStatementNumbersWithPartialRHS("1");

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::QuoutConst, "\"55\""),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")
    };



//    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
//    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
//    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
//
//    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
//    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
//    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
//    statementWriter->insertStatement(1);
//    statementWriter->insertStatement(2);
//    statementWriter->insertStatement(3);
//    statementWriter->insertStatement(4);
//    statementWriter->insertStatement(5);
//    assignPatternWriter->addAssignPattern(1, "y", "x + 1");
//    assignPatternWriter->addAssignPattern(2, "z", "11 + y");
//    assignPatternWriter->addAssignPattern(3, "x", "111 + x");
//    assignPatternWriter->addAssignPattern(4, "w", "1111");
//    assignPatternWriter->addAssignPattern(5, "x", "y + 5 + v");
//    assignWriter->insertAssign(1);
//    assignWriter->insertAssign(2);
//    assignWriter->insertAssign(3);
//    assignWriter->insertAssign(4);
//    assignWriter->insertAssign(5);

    std::shared_ptr<AssignPatternReader> dddd = pkbReaderManager->getAssignPatternReader();

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "9" });

}
