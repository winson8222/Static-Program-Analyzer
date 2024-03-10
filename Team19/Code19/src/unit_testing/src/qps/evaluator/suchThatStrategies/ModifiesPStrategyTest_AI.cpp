//#include "catch.hpp"
//#include "qps/evaluator/suchThatStrategies/ModifiesPStrategy.h"
//#include "pkb/PKBReaderManager.h"
//#include "pkb/PKB.h"
//#include "qps/parser/ParsingResult.h"
//#include "../../spa/src/qps/parser/QueryParser.h"
//#include "../../spa/src/pkb/PKBManager.h"
//#include "../../spa/src/qps/evaluator/QueryEvaluator.h"
//
//// Helper function for creating a ParsingResult tailored for Modifies tests
//ParsingResult createParsingResultForModifies(const std::string& entity, const std::string& variable, bool isProcedure) {
//    ParsingResult parsingResult;
//    parsingResult.setSuchThatClauseRelationship(Token(TokenType::ModifiesP, "Modifies"));
//    // Set the entity type appropriately
//    TokenType entityType = isProcedure ? TokenType::IDENT : TokenType::INTEGER;
//    parsingResult.setSuchThatClauseFirstParam(Token(entityType, entity));
//    parsingResult.setSuchThatClauseSecondParam(Token(TokenType::IDENT, variable));
//    return parsingResult;
//}