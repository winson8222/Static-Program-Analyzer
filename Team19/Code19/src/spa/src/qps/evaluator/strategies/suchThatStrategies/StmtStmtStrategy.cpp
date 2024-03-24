//
// Created by Winson Zheng on 15/2/24.
//

#include "StmtStmtStrategy.h"

using namespace std;



bool StmtStmtStrategy::isBothParamsInteger(const Token& firstParam, const Token& secondParam) {
    // Implementation to check if both parameters are integers
    return firstParam.getType() == TokenType::INTEGER && secondParam.getType() == TokenType::INTEGER;
}

void StmtStmtStrategy::setTrueIfRelationShipExist(const Token &firstParam, const Token &secondParam,
                                                  const std::shared_ptr<IRelationshipReader<int, int>> &reader,
                                                  std::shared_ptr<ResultTable> resultTable) {
    if (firstParam.getType() == TokenType::Wildcard) {

        if (!reader->getRelationshipsByValue(stoi(secondParam.getValue())).empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        if (!reader->getRelationshipsByKey(stoi(firstParam.getValue())).empty()) {
            resultTable->setAsTruthTable();
        }
    } else {

        if (reader->hasRelationship(stoi(firstParam.getValue()), stoi(secondParam.getValue()))) {
            resultTable->setAsTruthTable();
        }
    }

}

void StmtStmtStrategy::insertRowsWithTwoCols(const Token &firstParam, const Token &secondParam,std::shared_ptr<IRelationshipReader<int ,int>> reader,
                           const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable, PKBReaderManager &pkbReaderManager) {
    string firstStatementType = parsingResult.getDeclaredSynonyms().at(firstParam.getValue());
    string secondStatementType = parsingResult.getDeclaredSynonyms().at(secondParam.getValue());

    // Retrieve the relationships
    unordered_set<int> filteredParents;
    const unordered_set<int>& parents = reader->getKeys();

    filteredParents = getFilteredStmtsNumByType(parents, firstStatementType, pkbReaderManager);
    // Iterate through the preFollows set and find corresponding postFollows
    for (int stmt1 : filteredParents) {
        unordered_set<int> filteredChildren;
        unordered_set<int> children = reader->getRelationshipsByKey(stmt1);

        filteredChildren = getFilteredStmtsNumByType(children, secondStatementType, pkbReaderManager);
        // For each stmt1, iterate through all its postFollows
        for (int stmt2 : filteredChildren) {
            pair<string, string> col1Pair = make_pair<string, string>(firstParam.getValue(), to_string(stmt1));
            pair<string, string> col2Pair = make_pair<string, string>(secondParam.getValue(), to_string(stmt2));
            insertRowToTable(col1Pair, col2Pair, resultTable);

        }
    }
}

void StmtStmtStrategy::insertStmtRowsWithSingleCol(unordered_set<int> filteredStmts, shared_ptr<ResultTable> resultTable, string colName){
    unordered_set<string> filteredStmtsStr;
    convertIntSetToStringSet(filteredStmts,filteredStmtsStr);
    insertRowsWithSingleColumn(colName, filteredStmtsStr, resultTable);
}