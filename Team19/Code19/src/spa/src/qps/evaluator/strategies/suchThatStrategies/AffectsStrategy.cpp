#include "AffectsStrategy.h"

std::shared_ptr<ResultTable> AffectsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();

    const auto suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    if (!suchClause) {
        // If not the expected clause type, return empty result
        return resultTable;
    }

    if (firstParam.getType() == TokenType::IDENT && secondParam.getType() == TokenType::IDENT) {
        // Both parameters are synonyms, representing assignment statement numbers.
        processSynonyms(resultTable, parsingResult, pkbReaderManager);
    } else if (firstParam.getType() == TokenType::INTEGER && secondParam.getType() == TokenType::INTEGER) {
        // Both parameters are specific statement numbers; directly check Affects relationship.
        int stmt1 = std::stoi(firstParam.getValue());
        int stmt2 = std::stoi(secondParam.getValue());
        if (affectsReader->hasAffects(stmt1, stmt2)) {
            resultTable->setAsTruthTable();
        }
    } else {
        // Mixed parameter types: one is a specific statement number, and the other is a synonym.
        if (firstParam.getType() == TokenType::INTEGER) {
            processFirstParam(resultTable, parsingResult, pkbReaderManager);
        } else if (secondParam.getType() == TokenType::INTEGER) {
            processSecondParam(resultTable, parsingResult, pkbReaderManager);
        }
    }

    return resultTable;
}

void AffectsStrategy::processFirstParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    string col1 = firstParam.getValue();
    resultTable->insertAllColumns({col1});

    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = std::stoi(secondParam.getValue());

        // Get all statements that affect a specific statement number
        auto affectingStatements = affectsReader->getAffecting(stmtNum);
        for (int stmt : affectingStatements) {
            resultTable->insertNewRow({{col1, std::to_string(stmt)}});
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        // If the second parameter is a wildcard, fetch all statements that affect others
        auto allAffecting = affectsReader->getAllAffecting();
        for (int stmt : allAffecting) {
            resultTable->insertNewRow({{col1, std::to_string(stmt)}});
        }
    }
}

void AffectsStrategy::processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    string col2 = secondParam.getValue();
    resultTable->insertAllColumns({col2});

    if (firstParam.getType() == TokenType::INTEGER) {
        // Specific statement number provided for the first parameter
        int stmtNum = std::stoi(firstParam.getValue());

        // Get all statements that are affected by the specific statement number
        auto affectedStatements = affectsReader->getAffected(stmtNum);
        for (int stmt : affectedStatements) {
            resultTable->insertNewRow({{col2, std::to_string(stmt)}});
        }
    } else if (firstParam.getType() == TokenType::Wildcard) {
        // If the first parameter is a wildcard, fetch all statements that are affected by others
        auto allAffected = affectsReader->getAllAffected();
        for (int stmt : allAffected) {
            resultTable->insertNewRow({{col2, std::to_string(stmt)}});
        }
    }
}

void AffectsStrategy::processIntegerParams(std::shared_ptr<ResultTable> resultTable) {
    // Ensure both parameters are indeed integers
    if (firstParam.getType() == TokenType::INTEGER && secondParam.getType() == TokenType::INTEGER) {
        int firstStmtNum = std::stoi(firstParam.getValue());
        int secondStmtNum = std::stoi(secondParam.getValue());

        // Assuming getAffectsReader exists and provides a method to check direct Affects relationship
        if (affectsReader->hasAffects(firstStmtNum, secondStmtNum)) {
            // If an Affects relationship exists between these two specific statements, set the result table as a truth table
            resultTable->setAsTruthTable();
        }
    }
}


