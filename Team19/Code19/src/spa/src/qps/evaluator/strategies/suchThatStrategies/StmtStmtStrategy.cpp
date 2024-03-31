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
            std::pair<std::string, std::string> col1Pair = make_pair<std::string, std::string>(firstParam.getValue(), std::to_string(stmt1));
            std::pair<std::string, std::string> col2Pair = make_pair<std::string, std::string>(secondParam.getValue(), std::to_string(stmt2));
            insertRowToTable(col1Pair, col2Pair, resultTable);
        }
    }
}
