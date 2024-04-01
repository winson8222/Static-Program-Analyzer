#include "catch.hpp"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"

#include <memory>

TEST_CASE("stmt s1, s2; variable v; Select BOOLEAN such that not Follows(1, 2)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select BOOLEAN such that not Follows(1, 2)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "FALSE" });
}


TEST_CASE("stmt s1, s2; variable v; Select s1 such that not Follows(s1, 2)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select s1 such that not Follows(s1, 2)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "2", "3" });
}

TEST_CASE("stmt s1, s2; variable v; Select s1 such that not Follows(s1, 2) and Follows(s1, 3)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select s1 such that not Follows(s1, 2) and Follows(s1, 3)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "2" });
}


TEST_CASE("stmt s1, s2; variable v; Select s1 such that not Follows(s1, 2) and Follows(s2, 3)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select s1 such that not Follows(s1, 2) and Follows(s2, 3)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "2", "3" });
}

TEST_CASE("stmt s1, s2; variable v; Select s1 such that not Follows(s1, 2) and Follows(s1, s2)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select s1 such that not Follows(s1, 2) and Follows(s1, s2)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "2" });
}

TEST_CASE("stmt s1, s2; variable v; Select <s1, s2> such that not Follows(s1, s2)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select <s1, s2> such that not Follows(s1, s2)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "1 3", "2 2", "3 3", "1 1", "2 1", "3 2", "3 1" });
}



TEST_CASE("stmt s1, s2; variable v; Select s1 such that Follows(s2, 3) and not Follows(s1, 2)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select s1 such that Follows(s2, 3) and not Follows(s1, 2)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "2", "3" });
}


TEST_CASE("stmt s1, s2; variable v; Select <s1, s2> such that not Follows(s1, s2) and Follows(s1, 1)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select <s1, s2> such that not Follows(s1, s2) and Follows(s1, 1)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{});
}

TEST_CASE("stmt s1, s2; variable v; Select <s1, s2> such that not Follows(s1, s2) and Follows(s1, 3)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select <s1, s2> such that not Follows(s1, s2) and Follows(s1, 1)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{});
}


TEST_CASE("stmt s1, s2; variable v; Select <s1, s2> such that not Follows(s1, 3) and Follows(s1, 2)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select <s1, s2> such that not Follows(s1, 3) and Follows(s1, 2)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "1 1", "1 2", "1 3" });
}
// not between 2 ands
TEST_CASE("stmt s1, s2; variable v; Select s1 such that Follows(s1, s2) and not Follows(s1, 5) and Parent(1, 2)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	statementWriter->insertStatement(4);
	statementWriter->insertStatement(5);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	followWriter->addFollows(4, 5);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");

	std::string query = "stmt s1, s2; variable v; Select s1 such that Follows(s1, s2) and not Follows(s1, 5) and Parent(1, 2)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "1", "2" });
}


// more than 2 not
TEST_CASE("stmt s1, s2; variable v; Select s1 such that Follows(s1, s2) and not Follows(s1, 5) and not Parent(3, 2)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
	std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	statementWriter->insertStatement(4);
	statementWriter->insertStatement(5);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	followWriter->addFollows(4, 5);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");
	variableWriter->insertVariable("x");
	variableWriter->insertVariable("y");
	variableWriter->insertVariable("z");


	std::string query = "stmt s1, s2; variable v; Select s1 such that Follows(s1, s2) and not Follows(s1, 5) and Parent(1, 2)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "1", "2" });
}

// add variable as entities
TEST_CASE("stmt s1, s2; variable v; Select s1 such that Uses(s1, v) and not Follows(s1, 3) and Parent(1, 2)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
	std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr<ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr<UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	statementWriter->insertStatement(4);
	statementWriter->insertStatement(5);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	followWriter->addFollows(4, 5);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");
	variableWriter->insertVariable("x");
	variableWriter->insertVariable("y");
	variableWriter->insertVariable("z");

	std::string query = "stmt s1, s2; variable v; Select s1 such that Uses(s1, v) and not Follows(s1, 3) and Parent(1, 2)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set<std::string> res = evaluator.evaluateQuery();
	REQUIRE(res == std::unordered_set<std::string>{ "3", "1" });
}

TEST_CASE("stmt s1, s2; variable v; Select <v, s1, s2> such that Uses(s1, v) and not Uses(s2, v)") {
	std::shared_ptr <PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr <PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr <PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
	std::shared_ptr <VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
	std::shared_ptr <StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr <FollowsWriter> followWriter = pkbWriterManager->getFollowsWriter();
	std::shared_ptr <ParentWriter> parentWriter = pkbWriterManager->getParentWriter();
	std::shared_ptr <UsesSWriter> usesWriter = pkbWriterManager->getUsesSWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	followWriter->addFollows(1, 2);
	followWriter->addFollows(2, 3);
	followWriter->addFollows(4, 5);
	parentWriter->addParent(1, 2);
	usesWriter->addUsesS(1, "x");
	usesWriter->addUsesS(2, "y");
	usesWriter->addUsesS(3, "z");
	variableWriter->insertVariable("x");
	variableWriter->insertVariable("y");
	variableWriter->insertVariable("z");

	std::string query = "stmt s1, s2; variable v; Select <v, s1, s2> such that Uses(s1, v) and not Uses(s2, v)";
	Tokenizer tokenizer(query);
	auto tokens = tokenizer.tokenize();
	QueryParser parser(tokens);
	auto parsingResult = parser.parse();
	QueryEvaluator evaluator(pkbReaderManager, parsingResult);
	std::unordered_set <std::string> res = evaluator.evaluateQuery();
	REQUIRE(res
		== std::unordered_set <std::string>{
		"x 1 2", "y 2 1", "y 2 3", "x 1 3", "z 3 1", "z 3 2" });
}

