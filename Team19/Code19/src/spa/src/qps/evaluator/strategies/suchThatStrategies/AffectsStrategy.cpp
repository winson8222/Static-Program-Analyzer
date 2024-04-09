// AffectsStrategy.cpp
#include "AffectsStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>

void AffectsStrategy::setReader(PKBReaderManager& pkbReaderManager) {
    // Implementation specific to AffectsStrategy, e.g.:
    auto reader = pkbReaderManager.getAffectsReader();
    // Set this reader to a member variable or use it as needed
}

void AffectsStrategy::addTrueRelationships(std::shared_ptr<ResultTable> resultTable) {
//    // We are assuming the 'affectsReader' member variable is already set with the appropriate AffectsReader.
//    std::shared_ptr<AffectsReader> affectsReader = std::dynamic_pointer_cast<AffectsReader>(this->reader);
//    // Get all statements that affect other statements
//    std::unordered_set<int> allAffectingStmts = affectsReader->getAllAffecting();
//
//    // Iterate over each affecting statement
//    for (int affectingStmt : allAffectingStmts) {
//        // Get all statements that are affected by the current affecting statement
//        std::unordered_set<int> affectedStmts = affectsReader->getAffected(affectingStmt);
//
//        // Insert each pair (affectingStmt, affectedStmt) into the result table
//        for (int affectedStmt : affectedStmts) {
//            std::unordered_map<std::string, std::string> newRow;
//            newRow["Affecting"] = std::to_string(affectingStmt);  // Adjust column name as needed
//            newRow["Affected"] = std::to_string(affectedStmt);    // Adjust column name as needed
//            resultTable->insertNewRow(newRow);
//        }
//    }
}




std::shared_ptr<ResultTable> AffectsStrategy::evaluateQueryOptimised(PKBReaderManager& pkbReaderManager,
                                                                     const ParsingResult& parsingResult,
                                                                     const Clause& clause,
                                                                     std::shared_ptr<ResultTable> result) {
    return evaluateQueryOptimisedCommon(pkbReaderManager, parsingResult, clause, result);
}

std::shared_ptr<ResultTable> AffectsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager,
                                                            const ParsingResult& parsingResult,
                                                            const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
    setBothParams(clause);
    setReader(pkbReaderManager);

    if (isParamOfType(firstParam, TokenType::IDENT) && isParamOfType(secondParam, TokenType::IDENT)) {
        // Both parameters are synonyms, representing assignment statement numbers.
        processSynonyms(resultTable, parsingResult, pkbReaderManager);
    } else if (isParamOfType(firstParam, TokenType::IDENT)) {
        // Mixed parameter types: one is a specific statement number, and the other is a synonym.
        processFirstParam(resultTable, parsingResult, pkbReaderManager);
    } else if (isParamOfType(secondParam, TokenType::IDENT)) {
        processSecondParam(resultTable, parsingResult, pkbReaderManager);
    } else {
        // Both parameters are specific statement numbers
        processIntegerParams(resultTable);
    }
