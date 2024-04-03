#include "catch.hpp"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"
#include <filesystem>
#include <fstream>
#include <memory>

#include "sp/SourceProcessor.h"

// Test suite for evaluating integration between Parent*, Pattern, and Follows clauses
TEST_CASE("src/qps/evaluator/suchThatAndPatternStrategy/suchThatAndPatternStrategy") {
	// Setup shared PKBManager and related components for use in test cases
	auto pkbManager = std::make_shared<PKBManager>();
	auto pkbReaderManager = pkbManager->getPKBReaderManager();
    auto pkbCacheManager = pkbManager->getPKBCacheManager();
	auto pkbWriterManager = pkbManager->getPKBWriterManager();
	auto statementWriter = pkbWriterManager->getStatementWriter();
	auto parentTWriter = pkbWriterManager->getParentTWriter();
	auto whileWriter = pkbWriterManager->getWhileWriter();
	auto assignWriter = pkbWriterManager->getAssignWriter();
	auto assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
	auto ifWriter = pkbWriterManager->getIfWriter();
	auto followsWriter = pkbWriterManager->getFollowsWriter();

	// Test case for evaluating a simple Parent* query with an assignment pattern
	SECTION("Check Evaluation result of a simple select Parent* query ") {
		statementWriter->insertStatement(1);
		statementWriter->insertStatement(2);
		statementWriter->insertStatement(3);
		whileWriter->insertWhile(1);
		whileWriter->insertWhile(3);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(4);
		assignPatternWriter->addAssignPattern(2, "x", "'1''x''+'");
		assignPatternWriter->addAssignPattern(4, "x", "'2''x''+'");
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
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> actualResults = evaluator.evaluateQuery();
		std::unordered_set<std::string> expectedResults = { "1" };
		REQUIRE(actualResults == expectedResults);

	}

	SECTION("Check Evaluation result of a tuple select Parent* query with pattern") {
		statementWriter->insertStatement(1);
		statementWriter->insertStatement(2);
		statementWriter->insertStatement(3);
		whileWriter->insertWhile(1);
		whileWriter->insertWhile(3);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(4);
		assignPatternWriter->addAssignPattern(2, "x", "'1''x''+'");
		assignPatternWriter->addAssignPattern(4, "x", "'2''x''+'");
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
				Token(TokenType::LeftAngleBracket, "<"),
				Token(TokenType::IDENT, "w"),
				Token(TokenType::Comma, ","),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::RightAngleBracket, ">"),
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
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> actualResults = evaluator.evaluateQuery();
		std::unordered_set<std::string> expectedResults = { "2", "1 3" };
		//        REQUIRE(actualResults == expectedResults);

	}

	SECTION("Check Evaluation result of a simple select Parent* query + adding ifs ") {
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
		assignWriter->insertAssign(6);
		ifWriter->insertIf(5);
		assignPatternWriter->addAssignPattern(2, "x", "'1''x''+'");
		assignPatternWriter->addAssignPattern(4, "x", "'2''x''+'");
		assignPatternWriter->addAssignPattern(6, "x", "'1''x''+'");
		parentTWriter->addParentT(1, 2);
		parentTWriter->addParentT(1, 6);
		parentTWriter->addParentT(3, 4);
		parentTWriter->addParentT(5, 6);

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
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> actualResults = evaluator.evaluateQuery();
		std::unordered_set<std::string> expectedResults = { "1" };
		REQUIRE(actualResults == expectedResults);

	}


	SECTION("Check Evaluation result of pattern and follows") {

		statementWriter->insertStatement(1);
		statementWriter->insertStatement(2);
		statementWriter->insertStatement(3);
		statementWriter->insertStatement(4);
		followsWriter->addFollows(1, 2);
		assignPatternWriter->addAssignPattern(1, "x", "'1'");
		assignPatternWriter->addAssignPattern(2, "x", "'2'");
		assignPatternWriter->addAssignPattern(3, "x", "'3'");
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
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
	}

	SECTION("Pattern partial match with semi-string") {

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
		assignPatternWriter->clear();

		sp.parseSIMPLE();
		sp.extractAndPopulate();

		std::shared_ptr<AssignPatternReader> assignPatternReader = pkbReaderManager->getAssignPatternReader();
		std::shared_ptr<AssignReader> assignReader = pkbReaderManager->getAssignReader();
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

		std::shared_ptr<AssignPatternReader> dddd = pkbReaderManager->getAssignPatternReader();

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"11"});

	}

	//    SECTION("Check Evaluation result of nested assign with partial pattern match and transitive Uses") {
	//        statementWriter->insertStatement(10);
	//        statementWriter->insertStatement(11);
	//        statementWriter->insertStatement(12);
	//        statementWriter->insertStatement(13);
	//        whileWriter->insertWhile(10);
	//        ifWriter->insertIf(11);
	//        assignWriter->insertAssign(12);
	//        assignWriter->insertAssign(13);
	//
	//        assignPatternWriter->addAssignPattern(12, "x", "'y'"); // Directly uses 'y'
	//        assignPatternWriter->addAssignPattern(13, "x", "'z' + 'y'"); // Directly uses 'y'
	//        parentTWriter->addParentT(10, 11);
	//        parentTWriter->addParentT(11, 12);
	//        parentTWriter->addParentT(11, 13);
	//
	//        std::vector<Token> tokens = {
	//                Token(TokenType::DesignEntity, "assign"),
	//                Token(TokenType::IDENT, "a"),
	//                Token(TokenType::Semicolon, ";"),
	//                Token(TokenType::SelectKeyword, "Select"),
	//                Token(TokenType::IDENT, "a"),
	//                Token(TokenType::SuchKeyword, "such"),
	//                Token(TokenType::ThatKeyword, "that"),
	//                Token(TokenType::Uses, "Uses"),
	//                Token(TokenType::Lparenthesis, "("),
	//                Token(TokenType::IDENT, "a"),
	//                Token(TokenType::Comma, ","),
	//                Token(TokenType::QuoutIDENT, "'y'"),
	//                Token(TokenType::Rparenthesis, ")"),
	//                Token(TokenType::PatternKeyword, "pattern"),
	//                Token(TokenType::IDENT, "a"),
	//                Token(TokenType::Lparenthesis, "("),
	//                Token(TokenType::QuoutIDENT, "'x'"),
	//                Token(TokenType::Comma, ","),
	//                Token(TokenType::Wildcard, "_"),
	//                Token(TokenType::QuoutConst, "'y'"),
	//                Token(TokenType::Wildcard, "_"),
	//                Token(TokenType::Rparenthesis, ")")
	//        };
	//
	//
	//        QueryParser parser(tokens);
	//        auto parsingResult = parser.parse();
	//        QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
	//        std::unordered_set<std::string> actualResults = evaluator.evaluateQuery();
	//        std::unordered_set<std::string> expectedResults = {"12", "13"}; // Both statements should match
	//        REQUIRE(actualResults == expectedResults);
	//    }


			// Nested Assignments Within While Loops Modifying 'count'
	SECTION("Nested Assignments Within While Loops Modifying 'count'") {
		statementWriter->insertStatement(10); // while
		assignWriter->insertAssign(11); // assign directly nested
		ifWriter->insertIf(12);
		assignWriter->insertAssign(13); // assign indirectly nested
		whileWriter->insertWhile(10);
		assignPatternWriter->addAssignPattern(11, "count", "'x'");
		assignPatternWriter->addAssignPattern(13, "count", "'y''c''+'");
		parentTWriter->addParentT(10, 11);
		parentTWriter->addParentT(10, 12);
		parentTWriter->addParentT(12, 13);

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::DesignEntity, "while"),
				Token(TokenType::IDENT, "w"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::IDENT, "a"),
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
				Token(TokenType::QuoutIDENT, "\"count\""),
				Token(TokenType::Comma, ","),
				Token(TokenType::Wildcard, "_"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		auto actualResults = evaluator.evaluateQuery();
		std::unordered_set<std::string> expectedResults = { "11" }; // Both assignments modify "count"
		REQUIRE(actualResults == expectedResults);
	}


	// Q12: Assignments Using and Modifying the Same Variable
	//    SECTION("Assignments Using and Modifying the Same Variable") {
	//        statementWriter->insertStatement(6);
	//        statementWriter->insertStatement(7);
	//        statementWriter->insertStatement(8);
	//        statementWriter->insertStatement(12);
	//        statementWriter->insertStatement(13);
	//        auto usesWriter = pkbWriterManager->getUsesSWriter();
	//
	//        // Setup statements with Uses relationships
	//        usesWriter->addUsesS(6, "x");
	//        usesWriter->addUsesS(7, "x");
	//        usesWriter->addUsesS(8, "x");
	//        usesWriter->addUsesS(12, "x");
	//        usesWriter->addUsesS(13, "x");
	//
	//        assignPatternWriter->addAssignPattern(6, "x", "_");
	//        assignPatternWriter->addAssignPattern(7, "x", "_");
	//        assignPatternWriter->addAssignPattern(8, "x", "_");
	//        assignPatternWriter->addAssignPattern(12, "x", "_");
	//        assignPatternWriter->addAssignPattern(13, "x", "_");
	//
	//        std::vector<Token> tokens = {
	//                Token(TokenType::DesignEntity, "assign"),
	//                Token(TokenType::IDENT, "a"),
	//                Token(TokenType::Semicolon, ";"),
	//                Token(TokenType::DesignEntity, "variable"),
	//                Token(TokenType::IDENT, "v"),
	//                Token(TokenType::Semicolon, ";"),
	//                Token(TokenType::SelectKeyword, "Select"),
	//                Token(TokenType::IDENT, "a"),
	//                Token(TokenType::SuchKeyword, "such"),
	//                Token(TokenType::ThatKeyword, "that"),
	//                Token(TokenType::Uses, "Uses"),
	//                Token(TokenType::Lparenthesis, "("),
	//                Token(TokenType::IDENT, "a"),
	//                Token(TokenType::Comma, ","),
	//                Token(TokenType::IDENT, "v"),
	//                Token(TokenType::Rparenthesis, ")"),
	//                Token(TokenType::PatternKeyword, "pattern"),
	//                Token(TokenType::IDENT, "a"),
	//                Token(TokenType::Lparenthesis, "("),
	//                Token(TokenType::IDENT, "v"),
	//                Token(TokenType::Comma, ","),
	//                Token(TokenType::Wildcard, "_"),
	//                Token(TokenType::Rparenthesis, ")")
	//        };
	//
	//        // Parse and evaluate the query
	//        QueryParser parser(tokens);
	//        auto parsingResult = parser.parse();
	//        QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
	//        auto actualResults = evaluator.evaluateQuery();
	//        std::unordered_set<std::string> expectedResults = {"6", "7", "8", "12", "13"};
	//        REQUIRE(actualResults == expectedResults);
	//    }

	// Q13: Assignments Using and Modifying "x"
	SECTION("Assignments Using and Modifying 'x'") {
		// Assuming that the necessary setup with PKB has been completed
		statementWriter->insertStatement(14);
		statementWriter->insertStatement(15);
		auto usesWriter = pkbWriterManager->getUsesSWriter(); // Assuming this is the correct method to access UsesWriter

		// Setup statements with Uses relationships where "x" is not on the LHS
		usesWriter->addUsesS(14, "x");
		// Assuming '14' uses 'x' but does not assign to 'x'
		// Assuming '15' does not use 'x' at all

		assignPatternWriter->addAssignPattern(15, "y", "'x' + 1"); // '15' assigns 'y', not 'x'
		// No pattern added for '14' because it does not assign to 'x'

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::Uses, "Uses"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::Comma, ","),
				Token(TokenType::QuoutIDENT, "\"x\""),
				Token(TokenType::Rparenthesis, ")"),
				Token(TokenType::PatternKeyword, "pattern"),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::QuoutIDENT, "\"x\""),
				Token(TokenType::Comma, ","),
				Token(TokenType::Wildcard, "_"),
				Token(TokenType::Rparenthesis, ")")
		};

		// Parse and evaluate the query
		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		auto actualResults = evaluator.evaluateQuery();
		std::unordered_set<std::string> expectedResults; // No assignments modify and use "x" directly
		REQUIRE(actualResults == expectedResults);
	}

	SECTION("Check Evaluation result of pattern and follows") {

		statementWriter->insertStatement(1);
		statementWriter->insertStatement(2);
		statementWriter->insertStatement(3);
		statementWriter->insertStatement(4);
		followsWriter->addFollows(1, 2);
		assignPatternWriter->addAssignPattern(1, "x", "'1'");
		assignPatternWriter->addAssignPattern(2, "x", "'2'");
		assignPatternWriter->addAssignPattern(3, "x", "'3'");
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);


		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::PatternKeyword, "pattern"),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::Wildcard, "_"),
				Token(TokenType::Comma, ","),
				Token(TokenType::Wildcard, "_"),
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
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"TRUE"});
	}

	SECTION("Check Evaluation result of pattern and follows") {

		statementWriter->insertStatement(1);
		statementWriter->insertStatement(2);
		statementWriter->insertStatement(3);
		statementWriter->insertStatement(4);
		followsWriter->addFollows(1, 2);
		assignPatternWriter->addAssignPattern(1, "x", "'1'");
		assignPatternWriter->addAssignPattern(2, "x", "'2'");
		assignPatternWriter->addAssignPattern(3, "x", "'3'");
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);


		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::PatternKeyword, "pattern"),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::QuoutIDENT, "\"x\""),
				Token(TokenType::Comma, ","),
				Token(TokenType::QuoutConst, "\"1\""),
				Token(TokenType::Rparenthesis, ")"),

		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"TRUE"});
	}

	SECTION("Check Evaluation result of pattern and follows") {

		statementWriter->insertStatement(1);
		statementWriter->insertStatement(2);
		statementWriter->insertStatement(3);
		statementWriter->insertStatement(4);
		followsWriter->addFollows(1, 2);
		assignPatternWriter->addAssignPattern(1, "x", "'1'");
		assignPatternWriter->addAssignPattern(2, "x", "'2'");
		assignPatternWriter->addAssignPattern(3, "x", "'3'");
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);


		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::PatternKeyword, "pattern"),
				Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::QuoutIDENT, "\"x\""),
				Token(TokenType::Comma, ","),
				Token(TokenType::QuoutConst, "\"4\""),
				Token(TokenType::Rparenthesis, ")"),

		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"FALSE"});
	}


	SECTION("Pattern partial match with semi-string") {

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
		std::shared_ptr<AssignReader> assignReader = pkbReaderManager->getAssignReader();
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
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"11"});

	}

	//assign a, a1; variable v; stmt s;
	//Select a such that Follows (a, a1) pattern a(v, _)
	SECTION("src/qps/evaluator/BasicQueryFailure") {
		std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
		std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

		std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
		std::shared_ptr<FollowsWriter> followsWriter = pkbWriterManager->getFollowsWriter();
		std::shared_ptr<AssignWriter> assignWriter = pkbWriterManager->getAssignWriter();
		std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
		std::shared_ptr<VariableWriter> variableWriter = pkbWriterManager->getVariableWriter();
		statementWriter->insertStatement(1);
		statementWriter->insertStatement(2);
		statementWriter->insertStatement(3);
		statementWriter->insertStatement(4);
		statementWriter->insertStatement(5);
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(5);
		variableWriter->insertVariable("x");
		variableWriter->insertVariable("y");
		followsWriter->addFollows(1, 2);
		assignPatternWriter->addAssignPattern(1, "x", "'1'");
		assignPatternWriter->addAssignPattern(2, "y", "'2'");
		assignPatternWriter->addAssignPattern(5, "x", "'1'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"), Token(TokenType::Comma, ","),
				Token(TokenType::IDENT, "a1"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::DesignEntity, "variable"), Token(TokenType::IDENT, "v"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "stmt"), Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::IDENT, "a"), Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"), Token(TokenType::Follows, "Follows"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "a"), Token(TokenType::Comma, ","),
				Token(TokenType::IDENT, "a1"), Token(TokenType::Rparenthesis, ")"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "v"), Token(TokenType::Comma, ","),
				Token(TokenType::Wildcard, "_"), Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"1"});

	}

}

TEST_CASE("SuchThatPatternStrategy Evaluation") {

	SECTION("Evaluate Assign Pattern Strategy with Exact Match for Variable 'x' and Value '1'") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'1'");
		assignPatternWriter->addAssignPattern(3, "x", "'2'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::IDENT, "a"), Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::QuoutIDENT, "\"x\""),
				Token(TokenType::Comma, ","), Token(TokenType::QuoutConst, "\"1\""), Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"1"});
	}

	SECTION("Evaluate Assign Pattern Strategy with Variable Pattern Matching '1' Across Multiple Assignments") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'1'");
		assignPatternWriter->addAssignPattern(2, "y", "'1'");
		assignPatternWriter->addAssignPattern(3, "x", "'2'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "variable"),
				Token(TokenType::IDENT, "v"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"), Token(TokenType::IDENT, "a"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "v"), Token(TokenType::Comma, ","),
				Token(TokenType::QuoutConst, "\"1\""), Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"1", "2"});
	}

	SECTION("Evaluating AssignPattern with Variable Synonym Matching '1' in Assignments Returns Variable Names") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'1'");
		assignPatternWriter->addAssignPattern(2, "y", "'1'");
		assignPatternWriter->addAssignPattern(3, "x", "'2'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "variable"),
				Token(TokenType::IDENT, "v"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"), Token(TokenType::IDENT, "v"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "v"), Token(TokenType::Comma, ","),
				Token(TokenType::QuoutConst, "\"1\""), Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"x", "y"});
	}


	SECTION("Evaluating AssignPattern for Variable Synonyms in Diverse Assignments Returns Matching Variable Names") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'1'");
		assignPatternWriter->addAssignPattern(2, "y", "'1'");
		assignPatternWriter->addAssignPattern(3, "x", "'2'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "variable"),
				Token(TokenType::IDENT, "v"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"), Token(TokenType::IDENT, "v"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "v"), Token(TokenType::Comma, ","),
				Token(TokenType::QuoutConst, "\"1\""), Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"x", "y"});
	}

	SECTION("AssignPattern with Underscore and Specific Value Matches Only Relevant Assignments") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'1'");
		assignPatternWriter->addAssignPattern(2, "y", "'1'");
		assignPatternWriter->addAssignPattern(3, "x", "'2'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "variable"),
				Token(TokenType::IDENT, "v"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"), Token(TokenType::IDENT, "a"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::Wildcard, "_"), Token(TokenType::Comma, ","),
				Token(TokenType::QuoutConst, "\"2\""), Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"3"});
	}

	SECTION("AssignPattern with Variable and Underscore Matches Assignments with Specific Value") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'x''1''+''y''+''2''+'");
		assignPatternWriter->addAssignPattern(2, "y", "'1'");
		assignPatternWriter->addAssignPattern(3, "x", "'2'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "variable"),
				Token(TokenType::IDENT, "v"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"), Token(TokenType::IDENT, "a"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "v"), Token(TokenType::Comma, ","),
				Token(TokenType::Wildcard, "_"), Token(TokenType::QuoutConst, "\"2\""), Token(TokenType::Wildcard, "_"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"1", "3"});
	}

	SECTION("Matching AssignPatterns with Wildcards for Exact Expressions") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'x''1''+''y''+''2''+'");
		assignPatternWriter->addAssignPattern(2, "y", "'1'");
		assignPatternWriter->addAssignPattern(3, "x", "'2'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "variable"),
				Token(TokenType::IDENT, "v"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"), Token(TokenType::IDENT, "a"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "v"), Token(TokenType::Comma, ","),
				Token(TokenType::Wildcard, "_"), Token(TokenType::QuoutConst, "\"x+1\""),
				Token(TokenType::Wildcard, "_"), Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"1"});
	}

	SECTION("AssignPatternStrategy Evaluates Complex Expression Match with Wildcards") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'x''1''+''y''+''2''+'");
		assignPatternWriter->addAssignPattern(2, "y", "'1'");
		assignPatternWriter->addAssignPattern(3, "x", "'2'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "variable"),
				Token(TokenType::IDENT, "v"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"), Token(TokenType::IDENT, "a"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "v"), Token(TokenType::Comma, ","),
				Token(TokenType::Wildcard, "_"), Token(TokenType::QuoutConst, "\"x+1+y\""),
				Token(TokenType::Wildcard, "_"), Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"1"});
	}

	SECTION("AssignPatternStrategy Evaluates Complex Expression Match with Wildcards") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'x''1''+''y''+''2''+'");
		assignPatternWriter->addAssignPattern(2, "y", "'1'");
		assignPatternWriter->addAssignPattern(3, "x", "'4''x''-''z''+'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "variable"),
				Token(TokenType::IDENT, "v"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"), Token(TokenType::IDENT, "a"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "v"), Token(TokenType::Comma, ","),
				Token(TokenType::Wildcard, "_"), Token(TokenType::QuoutConst, "\"x+1+y+z\""),
				Token(TokenType::Wildcard, "_"), Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{});
	}


	SECTION("Variable Pattern Matching in Assignments with Specific Operations") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'x''1''+''y''+''2''+'");
		assignPatternWriter->addAssignPattern(2, "y", "'1''y''+'");
		assignPatternWriter->addAssignPattern(3, "z", "'4''x''-''z''+'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "variable"),
				Token(TokenType::IDENT, "v"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"), Token(TokenType::IDENT, "v"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "v"), Token(TokenType::Comma, ","),
				Token(TokenType::Wildcard, "_"), Token(TokenType::QuoutConst, "\"y\""), Token(TokenType::Wildcard, "_"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"x", "y"});
	}

	SECTION("Variable Pattern Matching in Assignments with Specific Operations") {
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
		assignWriter->insertAssign(1);
		assignWriter->insertAssign(2);
		assignWriter->insertAssign(3);
		assignPatternWriter->addAssignPattern(1, "x", "'x''1''+''y''+''2''+'");
		assignPatternWriter->addAssignPattern(2, "y", "'1''y''+'");
		assignPatternWriter->addAssignPattern(3, "z", "'x''2''+''y''+''x''1''+''+'");

		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "assign"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Semicolon, ";"), Token(TokenType::DesignEntity, "variable"),
				Token(TokenType::IDENT, "v"), Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"), Token(TokenType::IDENT, "v"),
				Token(TokenType::PatternKeyword, "pattern"), Token(TokenType::IDENT, "a"),
				Token(TokenType::Lparenthesis, "("), Token(TokenType::IDENT, "v"), Token(TokenType::Comma, ","),
				Token(TokenType::Wildcard, "_"), Token(TokenType::QuoutConst, "\"x+1\""),
				Token(TokenType::Wildcard, "_"), Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();

		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"x", "z"});
	}
}

TEST_CASE("if i; Select i such that Next(1, i) pattern i(_, _, _)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
	std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);

	ifWriter->insertIf(1);
	nextWriter->addNext(1, 2);
	nextWriter->addNext(1, 6);
}
