#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"
#include "catch.hpp"

using namespace std;
// Test for Parsing Result assuming that the query is valid
TEST_CASE("Check Evaluation result of a simple select all statements query") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);


    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "3", "2", "1" });

}

TEST_CASE("Check Evaluation result of a simple select all variables query") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
    string x = "x";
    string y = "y";
    string z = "z";
    variableWriter->insertVariable(x);
    variableWriter->insertVariable(y);
    variableWriter->insertVariable(z);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "variable"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "v"),

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "x", "y", "z" });

}

TEST_CASE("Check Evaluation result of a simple select all procedures query") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<ProcedureWriter> proWriter = pkbWriterManager->getProcedureWriter();
    string x = "main";
    string y = "proc1";
    proWriter->insertProcedure(x);
    proWriter->insertProcedure(y);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "procedure"),
            Token(TokenType::IDENT, "p"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "p"),

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "main", "proc1"});

}

TEST_CASE("Check Evaluation result of a simple select all procedures query with true clause") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<ProcedureWriter> proWriter = pkbWriterManager->getProcedureWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
    string x = "main";
    string y = "proc1";
    proWriter->insertProcedure(x);
    proWriter->insertProcedure(y);
    assignPatternWriter->addAssignPattern(1, "x", "1");
    assignWriter->insertAssign(1);





    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "procedure"),
            Token(TokenType::IDENT, "p"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "p"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Comma, ","),
            Token(TokenType::QuoutConst, "\"1\""),
            Token(TokenType::Rparenthesis, ")")
    };



    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "main", "proc1"});

}


TEST_CASE("Check Evaluation result of a simple select all whiles query") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    string x = "x";
    string y = "y";
    string z = "z";
    whileWriter->insertWhile(1);
    whileWriter->insertWhile(2);
    whileWriter->insertWhile(3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "while"),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "w"),

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "3", "2", "1" });

}


TEST_CASE("Check Evaluation result of a simple select pattern assign query") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "x", "1");
    assignPatternWriter->addAssignPattern(2, "x", "2");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);


    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Comma, ","),
            Token(TokenType::QuoutConst, "\"1\""),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "1" });

}

TEST_CASE("Check Evaluation result of a select pattern query with variable") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Comma, ","),
            Token(TokenType::QuoutIDENT, "\"y\""),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "2" });

}

TEST_CASE("Check Evaluation result of a select pattern query with wildcard on RHS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);


    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::QuoutIDENT, "\"x\""),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();

    REQUIRE((res == std::unordered_set<string>{ "3", "2" } || res == std::unordered_set<string>{"2", "3"}));

}

TEST_CASE("Check Evaluation result of a select pattern query with wildcard on RHS and LHS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);


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
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE((res == std::unordered_set<string>{ "3", "2", "1" } || res == std::unordered_set<string>{"1", "2", "3"}));

}

TEST_CASE("Check Evaluation result of a select pattern query with wildcard on LHS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std:shared_ptr<AssignPatternReader> assignPatternReader = pkbReaderManager->getAssignPatternReader();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);

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
            Token(TokenType::QuoutIDENT, "\"y\""),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "2" });

}

TEST_CASE("Check Evaluation result of a select variable query with assign pattern query with synonym on LHS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std:shared_ptr<AssignPatternReader> assignPatternReader = pkbReaderManager->getAssignPatternReader();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "variable"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Comma, ","),
            Token(TokenType::QuoutIDENT, "\"y\""),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "x" });

}

TEST_CASE("Check Evaluation result of a select variable query with assign pattern query with synonym on LHS and wild card on RHS") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std:shared_ptr<AssignPatternReader> assignPatternReader = pkbReaderManager->getAssignPatternReader();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();

    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    assignPatternWriter->addAssignPattern(1, "y", "1");
    assignPatternWriter->addAssignPattern(2, "x", "y");
    assignPatternWriter->addAssignPattern(3, "x", "3");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);

    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "assign"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "variable"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::PatternKeyword, "pattern"),
            Token(TokenType::IDENT, "a"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "y", "x" });

}

TEST_CASE("Check Evaluation result of a select pattern assign query with partial pattern on RHS and LHS with Wildcard") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
    std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    assignPatternWriter->addAssignPattern(1, "y", "x + 1");
    assignPatternWriter->addAssignPattern(2, "z", "2 + y");
    assignPatternWriter->addAssignPattern(3, "x", "3 + x");
    assignPatternWriter->addAssignPattern(4, "w", "x");
    assignWriter->insertAssign(1);
    assignWriter->insertAssign(2);
    assignWriter->insertAssign(3);
    assignWriter->insertAssign(4);


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
            Token(TokenType::QuoutConst, "\"x\""),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")
    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{ "1", "3", "4" });

}



TEST_CASE("Check Evaluation result of synonym for UsesS and select ifs") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
    std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addUsesS(2, "x");
    modifiesSWriter->addUsesS(3, "y");
    modifiesSWriter->addUsesS(4, "z");
    ifWriter->insertIf(2);
    whileWriter->insertWhile(3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "if"),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Uses, "Uses"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"2"});
}

TEST_CASE("Check Evaluation result of synonym for UsesS and select whiles") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<UsesSWriter> modifiesSWriter = pkbWriterManager->getUsesSWriter();
    std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addUsesS(2, "x");
    modifiesSWriter->addUsesS(3, "y");
    modifiesSWriter->addUsesS(4, "z");
    ifWriter->insertIf(2);
    whileWriter->insertWhile(3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "while"),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Uses, "Uses"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"3"});
}

TEST_CASE("Check Evaluation result of variable for UsesS and select ifs with wildcard") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<UsesSWriter> usesSWriter = pkbWriterManager->getUsesSWriter();
    std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);

    usesSWriter->addUsesS(2, "x");
    usesSWriter->addUsesS(3, "y");
    usesSWriter->addUsesS(4, "z");
    ifWriter->insertIf(2);
    whileWriter->insertWhile(3);



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
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"SemanticError"});

}


TEST_CASE("Check Evaluation result of variable for ModifiesS and select ifs with wildcard") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesSWriter> modifiesSWriter = pkbWriterManager->getModifiesSWriter();
    std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);

    modifiesSWriter->addModifiesS(2, "x");
    modifiesSWriter->addModifiesS(3, "y");
    modifiesSWriter->addModifiesS(4, "z");
    ifWriter->insertIf(2);
    whileWriter->insertWhile(3);



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
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "v"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"SemanticError"});

}

TEST_CASE("Check Evaluation result of synonym for Modifies and select whiles") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesSWriter> modifiesSWriter = pkbWriterManager->getModifiesSWriter();
    std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addModifiesS(2, "x");
    modifiesSWriter->addModifiesS(3, "y");
    modifiesSWriter->addModifiesS(4, "z");
    ifWriter->insertIf(2);
    whileWriter->insertWhile(3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "while"),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Modifies, "Modifies"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"3"});
}

TEST_CASE("Check Evaluation result of synonym for Modifies and select ifs") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ModifiesSWriter> modifiesSWriter = pkbWriterManager->getModifiesSWriter();
    std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    modifiesSWriter->addModifiesS(2, "x");
    modifiesSWriter->addModifiesS(3, "y");
    modifiesSWriter->addModifiesS(4, "z");
    ifWriter->insertIf(2);
    whileWriter->insertWhile(3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "if"),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Modifies, "Modifies"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::Comma, ","),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"2"});
}


TEST_CASE("Check Evaluation result of synonym for Follows and select ifs") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
    std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    parentWriter->addParent(1, 2);
    parentWriter->addParent(3,4);
    ifWriter->insertIf(2);
    whileWriter->insertWhile(3);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "if"),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Parent, "Parent"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::Wildcard, "_"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"2"});
}


TEST_CASE("Check Evaluation result of synonym for Follows and select ifs with while as parent") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
    std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    parentWriter->addParent(1, 2);
    parentWriter->addParent(2,3);
    parentWriter->addParent(3,4);
    ifWriter->insertIf(2);
    whileWriter->insertWhile(3);
    ifWriter->insertIf(4);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "if"),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::DesignEntity, "while"),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Parent, "Parent"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "ifs"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "w"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{"2"});
}


//stmt s;
//Select s such that Follows (s, s)
TEST_CASE("Check Evaluation result of synonym for Follows with same stmt being used as both params") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<FollowsWriter> followsWriter = pkbWriterManager->getFollowsWriter();
    std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    followsWriter->addFollows(1, 2);
    followsWriter->addFollows(2,3);
    followsWriter->addFollows(3,4);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Follows, "Follows"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{});
}


TEST_CASE("Check Evaluation result of synonym for Parent with same stmt being used as both params") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();


    std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
    std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
    std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
    std::shared_ptr<WhileWriter> whileWriter = pkbWriterManager->getWhileWriter();
    statementWriter->insertStatement(1);
    statementWriter->insertStatement(2);
    statementWriter->insertStatement(3);
    statementWriter->insertStatement(4);
    parentWriter->addParent(1, 2);
    parentWriter->addParent(2,3);
    parentWriter->addParent(3,4);



    std::vector<Token> tokens = {
            Token(TokenType::DesignEntity, "stmt"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Semicolon, ";"),
            Token(TokenType::SelectKeyword, "Select"),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::SuchKeyword, "such"),
            Token(TokenType::ThatKeyword, "that"),
            Token(TokenType::Parent, "Parent"),
            Token(TokenType::Lparenthesis, "("),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Comma, ","),
            Token(TokenType::IDENT, "s"),
            Token(TokenType::Rparenthesis, ")")

    };

    QueryParser parser(tokens);
    auto parsingResult = parser.parse();
    QueryEvaluator evaluator(pkbReaderManager, parsingResult);
    std::unordered_set<string> res = evaluator.evaluateQuery();
    REQUIRE(res == std::unordered_set<string>{});
}

//stmt s;
//Select s such that Follows (s, s)
TEST_CASE("Check Evaluation result of pattern and follows") {
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