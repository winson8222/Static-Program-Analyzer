#include "catch.hpp"
#include "qps/evaluator/strategies/suchThatStrategies/NextStrategy.h"
#include "pkb/PKBReaderManager.h"
#include "pkb/PKB.h"
#include "qps/parser/ParsingResult.h"
#include "qps/parser/QueryParser.h"
#include "pkb/PKBManager.h"
#include "qps/evaluator/QueryEvaluator.h"

TEST_CASE("src/qps/evaluator/suchThatStrategies/NextStrategy/1") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBCacheManager> pkbCacheManager = pkbManager->getPKBCacheManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	statementWriter->insertStatement(4);
	statementWriter->insertStatement(5);
	statementWriter->insertStatement(6);
	nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
	nextWriter->addNext(2, 3);
	nextWriter->addNext(3, 4);
	nextWriter->addNext(1, 4);
	nextWriter->addNext(5, 6);

	SECTION("NextStrategy/Verify Direct Next Relationship") {
		// Define tokens for the query
		std::vector<Token> tokens = {
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::Next, "Next"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::INTEGER, "2"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "3"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"TRUE"}); // Expect TRUE as 2 Next 3 is defined
	}

	SECTION("NextStrategy/Verify Next Relationship") {


		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::Next, "Next"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::INTEGER, "1"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "4"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"TRUE"});
	}

	SECTION("NextStrategy/Verify Next Relationship with 1 Int and 1 IDENT (FALSE)") {

		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "stmt"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::Next, "Next"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "1"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"FALSE"});
	}

	SECTION("NextStrategy/Verify Next Relationship with 1 Int and 1 IDENT (TRUE)") {


		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "stmt"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::Next, "Next"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "3"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"TRUE"});
	}

	SECTION("Select stmt from NextT Relationship") {


		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "stmt"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::Next, "Next"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "4"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"3", "1"});
	}

	SECTION("Select stmt from Next Relationship with 1 Int and 1 IDENT") {


		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "stmt"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::Next, "Next"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "4"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"3", "1"});
	}

	SECTION("NextTStrategy/Verify Direct NextT Relationship") {

		// Define tokens for the query
		std::vector<Token> tokens = {
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::NextT, "Next*"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::INTEGER, "2"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "3"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"TRUE"}); // Expect TRUE as 2 Next* 3 is defined
	}

	SECTION("NextTStrategy/Verify NextT Relationship") {
		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::NextT, "Next*"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::INTEGER, "1"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "5"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"FALSE"});
	}

	SECTION("NextTStrategy/Verify False NextT Relationship") {
		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::NextT, "Next*"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::INTEGER, "2"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "6"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"FALSE"});
	}

	SECTION("NextTStrategy/Verify NextT Relationship with 1 Int and 1 IDENT (FALSE)") {

		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "stmt"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::NextT, "Next*"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "1"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"FALSE"});
	}

	SECTION("NextTStrategy/Verify NextT Relationship with 1 Int and 1 IDENT (TRUE)") {


		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "stmt"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::NextT, "Next*"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "3"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"TRUE"});
	}

	SECTION("Select stmt from NextT Relationship with 1 Int and 1 IDENT") {


		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "stmt"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::NextT, "Next*"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "4"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"3", "1", "2"});
	}

	SECTION("Select stmt from NextT Relationship with 1 SYN and 1 Integer result") {


		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "stmt"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::NextT, "Next*"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::INTEGER, "2"),
				Token(TokenType::Comma, ","),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"3", "4"});
	}
}

TEST_CASE("src/qps/evaluator/suchThatStrategies/NextStrategy/2") {


	// Setup PKB with necessary entities and relationships
	auto pkbManager = std::make_shared<PKBManager>();
	auto pkbReaderManager = pkbManager->getPKBReaderManager();
    auto pkbCacheManager = pkbManager->getPKBCacheManager();
	auto pkbWriterManager = pkbManager->getPKBWriterManager();
	auto whileWriter = pkbWriterManager->getWhileWriter();
	auto nextWriter = pkbWriterManager->getNextWriter();
	auto statementWriter = pkbWriterManager->getStatementWriter();

	// Populate Next relationships as needed for the test cases
	// This setup assumes that statements 1-4 exist and are connected linearly
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	statementWriter->insertStatement(4);
	whileWriter->insertWhile(1);
	whileWriter->insertWhile(2);
	whileWriter->insertWhile(4);
	nextWriter->addNext(1, 2);
	nextWriter->addNext(2, 3);
	nextWriter->addNext(3, 4);
	nextWriter->addNext(1, 4);


	// Assuming PKBManager's cache or similar mechanism is updated after modifications

	SECTION("NextStrategy/Verify Direct NextT Relationship") {

		// Define tokens for the query
		std::vector<Token> tokens = {
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::BooleanKeyword, "BOOLEAN"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::NextT, "Next*"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::INTEGER, "2"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "3"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"TRUE"}); // Expect TRUE as 2 Next 3 is defined
	}

	SECTION("Select stmt from NextT Relationship with 1 SYN and 1 Integer result none") {

		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "stmt"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::NextT, "Next*"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::INTEGER, "4"),
				Token(TokenType::Comma, ","),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Rparenthesis, ")")
		};

		SECTION("Select while from NextT Relationship with 1 SYN and 1 Integer result none") {

			// Define tokens for the query testing transitive relationship
			std::vector<Token> tokens = {
					Token(TokenType::DesignEntity, "while"),
					Token(TokenType::IDENT, "w"),
					Token(TokenType::Semicolon, ";"),
					Token(TokenType::SelectKeyword, "Select"),
					Token(TokenType::IDENT, "w"),
					Token(TokenType::SuchKeyword, "such"),
					Token(TokenType::ThatKeyword, "that"),
					Token(TokenType::NextT, "Next*"),
					Token(TokenType::Lparenthesis, "("),
					Token(TokenType::IDENT, "w"),
					Token(TokenType::Comma, ","),
					Token(TokenType::INTEGER, "3"),
					Token(TokenType::Rparenthesis, ")")
			};

			QueryParser parser(tokens);
			auto parsingResult = parser.parse();
			QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
			std::unordered_set<std::string> res = evaluator.evaluateQuery();
			REQUIRE(res == std::unordered_set<std::string>{"1", "2"});
		}

		SECTION("Select stmt from Next Relationship with 1 wild card and 1 Integer") {
			// Define tokens for the query testing transitive relationship
			std::vector<Token> tokens = {
					Token(TokenType::DesignEntity, "stmt"),
					Token(TokenType::IDENT, "s"),
					Token(TokenType::Semicolon, ";"),
					Token(TokenType::SelectKeyword, "Select"),
					Token(TokenType::IDENT, "s"),
					Token(TokenType::SuchKeyword, "such"),
					Token(TokenType::ThatKeyword, "that"),
					Token(TokenType::Next, "Next"),
					Token(TokenType::Lparenthesis, "("),
					Token(TokenType::Wildcard, "_"),
					Token(TokenType::Comma, ","),
					Token(TokenType::INTEGER, "4"),
					Token(TokenType::Rparenthesis, ")")
			};

			QueryParser parser(tokens);
			auto parsingResult = parser.parse();
			QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
			std::unordered_set<std::string> res = evaluator.evaluateQuery();
			REQUIRE(res == std::unordered_set<std::string>{"3", "1", "2", "4"});
		}

		SECTION("Select stmt from Next Relationship with 2 stmt and multiple Select") {

			// Define tokens for the query testing transitive relationship
			std::vector<Token> tokens = {
					Token(TokenType::DesignEntity, "stmt"),
					Token(TokenType::IDENT, "s"),
					Token(TokenType::Comma, ","),
					Token(TokenType::IDENT, "s1"),
					Token(TokenType::Semicolon, ";"),
					Token(TokenType::SelectKeyword, "Select"),
					Token(TokenType::LeftAngleBracket, "<"),
					Token(TokenType::IDENT, "s"),
					Token(TokenType::Comma, ","),
					Token(TokenType::IDENT, "s1"),
					Token(TokenType::RightAngleBracket, ">"),
					Token(TokenType::SuchKeyword, "such"),
					Token(TokenType::ThatKeyword, "that"),
					Token(TokenType::Next, "Next"),
					Token(TokenType::Lparenthesis, "("),
					Token(TokenType::IDENT, "s"),
					Token(TokenType::Comma, ","),
					Token(TokenType::IDENT, "s1"),
					Token(TokenType::Rparenthesis, ")")
			};

			QueryParser parser(tokens);
			auto parsingResult = parser.parse();
			QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
			std::unordered_set<std::string> res = evaluator.evaluateQuery();
			REQUIRE(res == std::unordered_set<std::string>{"3 4", "1 4", "2 3", "1 2"});
		}
		SECTION("Select stmt from NextT Relationship with 2 stmt and multiple Select") {
			//Define tokens for the query testing transitive relationship
			std::vector<Token> tokens = {
					Token(TokenType::DesignEntity, "stmt"),
					Token(TokenType::IDENT, "s"),
					Token(TokenType::Comma, ","),
					Token(TokenType::IDENT, "s1"),
					Token(TokenType::Semicolon, ";"),
					Token(TokenType::SelectKeyword, "Select"),
					Token(TokenType::LeftAngleBracket, "<"),
					Token(TokenType::IDENT, "s"),
					Token(TokenType::Comma, ","),
					Token(TokenType::IDENT, "s1"),
					Token(TokenType::RightAngleBracket, ">"),
					Token(TokenType::SuchKeyword, "such"),
					Token(TokenType::ThatKeyword, "that"),
					Token(TokenType::NextT, "Next*"),
					Token(TokenType::Lparenthesis, "("),
					Token(TokenType::IDENT, "s"),
					Token(TokenType::Comma, ","),
					Token(TokenType::IDENT, "s1"),
					Token(TokenType::Rparenthesis, ")")
			};

			QueryParser parser(tokens);
			auto parsingResult = parser.parse();
			QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
			std::unordered_set<std::string> res = evaluator.evaluateQuery();
			REQUIRE(res == std::unordered_set<std::string>{"3 4", "1 3", "2 4", "1 1", "2 2", "1 2", "4 4", "2 3", "1 4"});
		}


	}

}

TEST_CASE("src/qps/evaluator/suchThatStrategies/NextStrategy/3") {
	// Setup PKB with NextT relationships
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBCacheManager> pkbCacheManager = pkbManager->getPKBCacheManager();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

	std::shared_ptr<NextWriter> nextWriter = pkbWriterManager->getNextWriter();
	std::shared_ptr<StatementWriter> statementWriter = pkbWriterManager->getStatementWriter();
	statementWriter->insertStatement(1);
	statementWriter->insertStatement(2);
	statementWriter->insertStatement(3);
	statementWriter->insertStatement(4);
	statementWriter->insertStatement(5);
	nextWriter->addNext(1, 2); // Direct relationships to simulate NextT
	nextWriter->addNext(2, 3);
	nextWriter->addNext(3, 4);
	nextWriter->addNext(1, 4);

	SECTION("Select stmt from NextT Relationship with 1 wild card and 1 Integer") {

		// Define tokens for the query testing transitive relationship
		std::vector<Token> tokens = {
				Token(TokenType::DesignEntity, "stmt"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::Semicolon, ";"),
				Token(TokenType::SelectKeyword, "Select"),
				Token(TokenType::IDENT, "s"),
				Token(TokenType::SuchKeyword, "such"),
				Token(TokenType::ThatKeyword, "that"),
				Token(TokenType::NextT, "Next*"),
				Token(TokenType::Lparenthesis, "("),
				Token(TokenType::Wildcard, "_"),
				Token(TokenType::Comma, ","),
				Token(TokenType::INTEGER, "4"),
				Token(TokenType::Rparenthesis, ")")
		};

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"3", "1", "2", "4", "5"});
	}

	SECTION("Select Boolean from Next Relationship with 2 Integer") {

		std::string query = "stmt s; Select BOOLEAN such that Next(2, 1)";
		Tokenizer tokenizer(query);
		std::vector<Token> tokens = tokenizer.tokenize();

		QueryParser parser(tokens);
		auto parsingResult = parser.parse();
		QueryEvaluator evaluator(pkbReaderManager, pkbCacheManager, parsingResult);
		std::unordered_set<std::string> res = evaluator.evaluateQuery();
		REQUIRE(res == std::unordered_set<std::string>{"FALSE"});
	}


}

TEST_CASE("Next Optimisation") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    std::shared_ptr<PKBCacheManager> pkbCacheManager = pkbManager->getPKBCacheManager();
    SECTION("IntraGroup prioritise one constant and one Synonym") {
        std::string query = "stmt s1, s2, s3, s4; Select s1 such that Next*(s1,s2) and Next*(s2,s3) and Next*(s3,s4) and Next*(s1, 2)";
        Tokenizer tokenizer = Tokenizer(query);
        std::vector<Token> tokens = tokenizer.tokenize();
        QueryParser parser(tokens);
        auto parsingResult = parser.parse();
        QueryEvaluator evaluator = QueryEvaluator(pkbReaderManager, pkbCacheManager, parsingResult);
        std::unordered_set<std::string> res = evaluator.evaluateQuery();
        REQUIRE(res == std::unordered_set<std::string>{ });
    }
}



