//#include "ModifiesPStrategy.h"
//
//std::shared_ptr<ResultTable> ModifiesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult)
//{
//    auto resultTable = make_shared<ResultTable>();
////    this->modifiesPReader= pkbReaderManager.getModifiesPReader();
////
////
////    const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
////    const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();
////
////    if (suchThatFirstParam.getType() == TokenType::IDENT && suchThatSecondParam.getType() == TokenType::IDENT) {
////        processBothSynonyms(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
////    } else if (suchThatFirstParam.getType() == TokenType::IDENT) {
////        processFirstParam(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
////    } else if (suchThatSecondParam.getType() == TokenType::IDENT) {
////        processSecondParam(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
////    } else if (suchThatFirstParam.getType() == TokenType::INTEGER  && suchThatSecondParam.getType() == TokenType::QuoutIDENT) {
////        processBothConstants(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable);
////    } else if (suchThatFirstParam.getType() == TokenType::Wildcard || suchThatSecondParam.getType() == TokenType::Wildcard) {
////        processWildCards(suchThatFirstParam, suchThatSecondParam, resultTable);
////    } else {
////        throw "Invalid Query!";
////    }
//    return resultTable;
//}
//
//void ModifiesPStrategy::processBothSynonyms(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
//        ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) {
//    return;
//}
//
//void ModifiesPStrategy::processFirstParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
//        ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) {
//    // get all statements that modifies a variable
//    return;
//}
//
//
//void ModifiesPStrategy::processSecondParam(const Token &firstParam, const Token &secondParam,
//                                          const ParsingResult &parsingResult,
//                                          std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) {
//    return;
//}
//
//void ModifiesPStrategy::processBothConstants(const Token &firstParam, const Token &secondParam,
//                                            const ParsingResult &parsingResult,
//                                            std::shared_ptr<ResultTable> resultTable) {
//    // check if the statement modifies the variable
//    return;
//}
//
//void ModifiesPStrategy::processWildCards(const Token& firstParam, const Token& secondParam, std::shared_ptr<ResultTable> resultTable) {
//    // check if there is any statement that modifies a variable
//    return;
//}