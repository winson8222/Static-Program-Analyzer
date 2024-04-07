#include "StmtStmtStrategy.h"
#include <memory>
#include <string>
#include <utility>
#include <unordered_set>

bool StmtStmtStrategy::isBothParamsInteger(const Token& firstParam, const Token& secondParam) {
    // Implementation to check if both parameters are integers
    return firstParam.getType() == TokenType::INTEGER && secondParam.getType() == TokenType::INTEGER;
}

void StmtStmtStrategy::setTrueIfRelationShipExist(const Token &firstParam, const Token &secondParam,
                                                  const std::shared_ptr<IRelationshipReader<int, int>> &reader,
                                                  std::shared_ptr<ResultTable> resultTable) {
    if (firstParam.getType() == TokenType::Wildcard) {

        if (!reader->getRelationshipsByValue(std::stoi(secondParam.getValue())).empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        if (!reader->getRelationshipsByKey(std::stoi(firstParam.getValue())).empty()) {
            resultTable->setAsTruthTable();
        }
    } else {

        if (reader->hasRelationship(std::stoi(firstParam.getValue()), std::stoi(secondParam.getValue()))) {
            resultTable->setAsTruthTable();
        }
    }
}

void StmtStmtStrategy::insertRowsWithTwoCols(const Token &firstParam, const Token &secondParam,std::shared_ptr<IRelationshipReader<int ,int>> reader,
                           const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable, PKBReaderManager &pkbReaderManager) {
    std::string firstParamValue = firstParam.getValue();
    std::string secondParamValue = secondParam.getValue();
    const std::string& firstStatementType = parsingResult.getRequiredSynonymType(firstParamValue);
    const std::string& secondStatementType = parsingResult.getRequiredSynonymType(secondParamValue);
    // Retrieve the relationships
    std::unordered_set<int> filteredParents;
    const std::unordered_set<int>& parents = reader->getKeys();

    filteredParents = getFilteredStmtsNumByType(parents, firstStatementType, pkbReaderManager);
    // Iterate through the preFollows set and find corresponding postFollows
    for (int stmt1 : filteredParents) {
        std::unordered_set<int> filteredChildren;
        std::unordered_set<int> children = reader->getRelationshipsByKey(stmt1);

        filteredChildren = getFilteredStmtsNumByType(children, secondStatementType, pkbReaderManager);
        // For each stmt1, iterate through all its postFollows
        for (int stmt2 : filteredChildren) {
            std::pair<std::string, std::string> col1Pair = std::make_pair<std::string, std::string>(firstParam.getValue(), std::to_string(stmt1));
            std::pair<std::string, std::string> col2Pair = std::make_pair<std::string, std::string>(secondParam.getValue(), std::to_string(stmt2));
            insertRowToTable(col1Pair, col2Pair, resultTable);
        }
    }
}



void StmtStmtStrategy::processSynonyms(std::shared_ptr<ResultTable> resultTable, const ParsingResult &parsingResult,
                                      PKBReaderManager &pkbReaderManager) {

    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();
    insertColsToTable(firstParam, secondParam, resultTable);
    // Choose the correct reader based on the variant indicating "Next" or "Next*"
    std::shared_ptr<IRelationshipReader<int, int>> affectsReader = getReader();
    insertRowsWithTwoCols(firstParam, secondParam, affectsReader, parsingResult, resultTable, pkbReaderManager);

}

void StmtStmtStrategy::processFirstParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();
    std::shared_ptr<IRelationshipReader<int, int>> reader = getReader();
    std::string colName = firstParam.getValue();
    resultTable->insertAllColumns({colName});
    std::unordered_set<std::string> keyStatementsInString;
    std::unordered_set<int> keyStatements;
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = std::stoi(secondParam.getValue());
        // Get all statements that affect a specific statement number
        keyStatements = reader->getRelationshipsByValue(stmtNum);
    } else if (secondParam.getType() == TokenType::Wildcard) {
        // If the second parameter is a wildcard, fetch all statements that affect others
        keyStatements = reader->getKeys();
    }

    std::string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    std::unordered_set<int> allFilteredAffectingStmts = getFilteredStmtsNumByType(keyStatements, statementType, pkbReaderManager);
    insertStmtRowsWithSingleCol(allFilteredAffectingStmts, resultTable, colName);
}

void StmtStmtStrategy::processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();
    std::shared_ptr<IRelationshipReader<int, int>> reader = getReader();
    std::string colName = secondParam.getValue();
    resultTable->insertAllColumns({colName});
    std::unordered_set<std::string> affectedStatementsInString;
    std::unordered_set<int> valueStatements;
    if (firstParam.getType() == TokenType::INTEGER) {
        // Specific statement number provided for the first parameter
        int stmtNum = std::stoi(firstParam.getValue());
        // Get all statements that are affected by the specific statement number
        valueStatements = reader->getRelationshipsByKey(stmtNum);
    } else if (firstParam.getType() == TokenType::Wildcard) {
        // If the first parameter is a wildcard, fetch all statements that are affected by others
        valueStatements = reader->getValues();
    }
    std::string statementType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    std::unordered_set<int> allFilteredAffectedStmts = getFilteredStmtsNumByType(valueStatements, statementType, pkbReaderManager);
    insertStmtRowsWithSingleCol(allFilteredAffectedStmts, resultTable, colName);
}

void StmtStmtStrategy::processIntegerParams(std::shared_ptr<ResultTable> resultTable) {
    // Ensure both parameters are indeed integers
    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();
    std::shared_ptr<IRelationshipReader<int, int>> reader = getReader();
    bool relationshipExists;
    if (isBothParamsWildcard(firstParam, secondParam)) {
        // If both params are wildcards, we can just check if there is a next statement
        relationshipExists = !reader->getValues().empty();
        if (relationshipExists) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(firstParam, secondParam, reader, resultTable);
    }
}

void StmtStmtStrategy::setReader(const std::shared_ptr<IRelationshipReader<int, int>> &reader) {
    this->reader = reader;
}

std::shared_ptr<IRelationshipReader<int, int>> StmtStmtStrategy::getReader() {
    return reader;
}
