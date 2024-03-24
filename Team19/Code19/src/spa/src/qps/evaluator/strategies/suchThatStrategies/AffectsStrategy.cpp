#include "AffectsStrategy.h"

std::shared_ptr<ResultTable> AffectsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
    this->affectsReader = pkbReaderManager.getAffectsReader();

    const auto suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->firstParam = suchClause->getFirstParam();
    this->secondParam = suchClause->getSecondParam();

    if (firstParam.getType() == TokenType::IDENT && secondParam.getType() == TokenType::IDENT) {
        // Both parameters are synonyms, representing assignment statement numbers.
        processSynonyms(resultTable, parsingResult, pkbReaderManager);
    } else if (firstParam.getType() == TokenType::IDENT ) {
        // Mixed parameter types: one is a specific statement number, and the other is a synonym.
            processFirstParam(resultTable, parsingResult, pkbReaderManager);

    } else if (secondParam.getType() == TokenType::IDENT) {
            processSecondParam(resultTable, parsingResult, pkbReaderManager);
    } else {
        // Both parameters are specific statement numbers
        processIntegerParams(resultTable);
    }

    return resultTable;
}

void AffectsStrategy::processSynonyms(std::shared_ptr<ResultTable> resultTable, const ParsingResult &parsingResult,
                                      PKBReaderManager &pkbReaderManager) {
    insertColsToTable(firstParam, secondParam, resultTable);
    // Choose the correct reader based on the variant indicating "Next" or "Next*"

    string firstParamType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    unordered_set<int> allAffectingStmts = affectsReader->getAllAffecting();
    unordered_set<int> filteredAffectingStmts = getFilteredStmtsNumByType(allAffectingStmts, firstParamType, pkbReaderManager);

    for (const int stmt : filteredAffectingStmts) {
        unordered_set<int> allAffectedStmts = affectsReader->getRelationshipsByKey(stmt);
        string secondStatementType = parsingResult.getDeclaredSynonym(secondParam.getValue());
        unordered_set<int> filteredAffectedStmts = getFilteredStmtsNumByType(allAffectedStmts, secondStatementType, pkbReaderManager);
        for (int nextStmt : filteredAffectedStmts) {
            // Insert each relevant pair into the result table
            std::pair<string, string> col1Pair = make_pair<string, string>(firstParam.getValue(), to_string(stmt));
            std::pair<string, string> col2Pair = make_pair<string, string>(secondParam.getValue(), to_string(nextStmt));
            insertRowToTable(col1Pair, col2Pair, resultTable);
        }
    }

}

void AffectsStrategy::processFirstParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    string colName = firstParam.getValue();
    resultTable->insertAllColumns({colName});
    unordered_set<string> affectingStatementsInString;
    unordered_set<int> affectingStatements;
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = std::stoi(secondParam.getValue());
        // Get all statements that affect a specific statement number
        affectingStatements = affectsReader->getAffecting(stmtNum);
    } else if (secondParam.getType() == TokenType::Wildcard) {
        // If the second parameter is a wildcard, fetch all statements that affect others
        affectingStatements = affectsReader->getAllAffecting();
    }

    string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    std::unordered_set<int> allFilteredAffectingStmts = getFilteredStmtsNumByType(affectingStatements, statementType, pkbReaderManager);
    convertIntSetToStringSet(allFilteredAffectingStmts , affectingStatementsInString);
    insertRowsWithSingleColumn(colName, affectingStatementsInString, resultTable);
}

void AffectsStrategy::processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    string colName = secondParam.getValue();
    resultTable->insertAllColumns({colName});
    unordered_set<string> affectedStatementsInString;
    unordered_set<int> affectedStatements;
    if (firstParam.getType() == TokenType::INTEGER) {
        // Specific statement number provided for the first parameter
        int stmtNum = std::stoi(firstParam.getValue());
        // Get all statements that are affected by the specific statement number
        affectedStatements = affectsReader->getAffected(stmtNum);
    } else if (firstParam.getType() == TokenType::Wildcard) {
        // If the first parameter is a wildcard, fetch all statements that are affected by others
        affectedStatements = affectsReader->getAllAffected();
    }
    string statementType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    std::unordered_set<int> allFilteredAffectedStmts = getFilteredStmtsNumByType(affectedStatements, statementType, pkbReaderManager);
    convertIntSetToStringSet(allFilteredAffectedStmts, affectedStatementsInString);
    insertRowsWithSingleColumn(colName, affectedStatementsInString, resultTable);
}

void AffectsStrategy::processIntegerParams(std::shared_ptr<ResultTable> resultTable) {
    // Ensure both parameters are indeed integers
    bool relationshipExists;
    if (isBothParamsWildcard(firstParam, secondParam)) {
        // If both params are wildcards, we can just check if there is a next statement
        relationshipExists = !affectsReader->getAllAffected().empty();
        if (relationshipExists) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(firstParam, secondParam, affectsReader, resultTable);
    }
}


