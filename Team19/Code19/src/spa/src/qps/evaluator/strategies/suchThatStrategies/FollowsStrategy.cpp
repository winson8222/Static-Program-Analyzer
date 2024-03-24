#include "FollowsStrategy.h"
#include "qps/parser/Token.h" // Include for Token definition

// Standard library dependencies
#include <string>
#include <unordered_set>
#include <iostream>

/**
 * Evaluates Follows or Follows* queries between two statements.
 * Determines the relationship based on the parsing result and updates the result table accordingly.
 *
 * @param pkbReaderManager Provides access to the program knowledge base.
 * @param parsingResult Contains the parsed query details.
 * @return A shared pointer to the populated result table.
 */
std::shared_ptr<ResultTable> FollowsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();

    // Initializing PKB readers for Follows relationships
    followsReader = pkbReaderManager.getFollowsReader();
    followsTReader = pkbReaderManager.getFollowsTReader();
    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->firstParam = suchClause->getFirstParam();
    this->secondParam = suchClause->getSecondParam();
    this->variant = suchClause->getRelationship().getValue();

    // Handling different parameter types for the Follows relationship
    if (isBothParamsSynonym(firstParam, secondParam)) {
        processSynonyms(resultTable, parsingResult, pkbReaderManager);
    } else if (firstParam.getType() == TokenType::IDENT) {
        processFirstParam(resultTable, parsingResult, pkbReaderManager);
    } else if (secondParam.getType() == TokenType::IDENT) {
        processSecondParam(resultTable, parsingResult, pkbReaderManager);
    } else if (isBothParamsWildcard(firstParam, secondParam)) {
        bool hasRelationship = (variant == "Follows") ?
                               !followsReader->isEmpty():
                               !followsTReader->isEmpty();
        if (hasRelationship) {
            resultTable->setAsTruthTable();
        }
    } else if (isBothParamsInteger(firstParam, secondParam)) {
        processIntegerParams(resultTable); // Handling integer cases
    }

    return resultTable;
}

/**
 * Processes cases where both parameters in the query are synonyms.
 * Populates the result table with pairs of statements that satisfy the Follows relationship.
 *
 * @param firstParam The first parameter of the query, a synonym.
 * @param secondParam The second parameter of the query, another synonym.
 * @param variant Specifies whether it's a direct Follows or transitive Follows* relationship.
 * @param resultTable The table to be populated with query results.
 */
void FollowsStrategy::processSynonyms(std::shared_ptr<ResultTable> resultTable,
                                      const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    insertColsToTable(firstParam, secondParam, resultTable);

    string firstStatementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    string secondStatementType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    unordered_set<int> filteredPreFollows;
    unordered_set<int> allPreFollowsStmts = variant == "Follows" ? followsReader->getAllPreFollows() : followsTReader->getAllPreFollowsT();
    filteredPreFollows = getFilteredStmtsNumByType(allPreFollowsStmts, firstStatementType, pkbReaderManager);

    for (int stmt1 : filteredPreFollows) {
        unordered_set<int> filteredPostFollows;
        auto postFollows = variant == "Follows" ? followsReader->getPostFollows(stmt1) : followsTReader->getPostFollowsT(stmt1);
        filteredPostFollows = getFilteredStmtsNumByType(postFollows, secondStatementType, pkbReaderManager);
        for (int stmt2 : filteredPostFollows) {
            // if the two synonyms are the same, add only one col and the 2 value must be the same
            pair<string, string> col1Pair = make_pair<string, string>(firstParam.getValue(), to_string(stmt1));
            pair<string, string> col2Pair = make_pair<string, string>(secondParam.getValue(), to_string(stmt2));
            insertRowToTable(col1Pair, col2Pair, resultTable);
        }
    }
}

/**
 * Processes queries where the first parameter is a synonym and the second parameter is specific.
 * This includes handling both integer and wildcard second parameters.
 *
 * @param firstParam The first parameter token of the query, expected to be a synonym.
 * @param secondParam The second parameter token of the query, can be an integer or a wildcard.
 * @param variant Specifies whether it's a direct Follows or transitive Follows* relationship.
 * @param resultTable The table to be populated with query results.
 */
void FollowsStrategy::processFirstParam(
                                        std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult,
                                        PKBReaderManager& pkbReaderManager) {
    string col1 = firstParam.getValue();
    resultTable->insertAllColumns({col1});
    string firstStatementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    unordered_set<int> filteredPreFollows;
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = std::stoi(secondParam.getValue());

        const auto& follows = (variant == "Follows") ?
                              followsReader->getPreFollows(stmtNum) :
                              followsTReader->getPreFollowsT(stmtNum);
        filteredPreFollows = getFilteredStmtsNumByType(follows, firstStatementType, pkbReaderManager);
        for (int stmt : filteredPreFollows) {
            resultTable->insertNewRow({{col1, std::to_string(stmt)}});
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        const auto& follows = (variant == "Follows") ?
                              followsReader->getAllPreFollows() :
                              followsTReader->getAllPreFollowsT();
        filteredPreFollows = getFilteredStmtsNumByType(follows, firstStatementType, pkbReaderManager);
        for (int stmt : filteredPreFollows) {
            resultTable->insertNewRow({{col1, std::to_string(stmt)}});
        }
    }
}

/**
 * Processes queries where the second parameter is a synonym and the first parameter is specific.
 * Handles both integer and wildcard first parameters.
 *
 * @param firstParam The first parameter token of the query, can be an integer or a wildcard.
 * @param secondParam The second parameter token of the query, expected to be a synonym.
 * @param variant Specifies whether it's a direct Follows or transitive Follows* relationship.
 * @param resultTable The table to be populated with query results.
 */
void FollowsStrategy::processSecondParam(
                                         std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult,
                                         PKBReaderManager& pkbReaderManager) {
    string col2 = secondParam.getValue();
    resultTable->insertAllColumns({col2});
    string secondStatementType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    unordered_set<int> filteredPostFollows;
    if (firstParam.getType() == TokenType::INTEGER) {
        int stmtNum = std::stoi(firstParam.getValue());
        const auto& follows = (variant == "Follows") ?
                              followsReader->getPostFollows(stmtNum) :
                              followsTReader->getPostFollowsT(stmtNum);

        filteredPostFollows = getFilteredStmtsNumByType(follows, secondStatementType, pkbReaderManager);

        for (int stmt : filteredPostFollows) {
            resultTable->insertNewRow({{col2, std::to_string(stmt)}});
        }
    } else if (firstParam.getType() == TokenType::Wildcard) {
        const auto& follows = (variant == "Follows") ?
                              followsReader->getAllPostFollows() :
                              followsTReader->getAllPostFollowsT();

        filteredPostFollows = getFilteredStmtsNumByType(follows, secondStatementType, pkbReaderManager);

        for (int stmt : filteredPostFollows) {
            resultTable->insertNewRow({{col2, std::to_string(stmt)}});
        }
    }
}

/**
 * Processes queries where both parameters are integers, determining if a direct Follows relationship exists.
 * Sets the result table as a truth table if the relationship is found.
 *
 * @param firstParam The first parameter token of the query, an integer representing a statement number.
 * @param secondParam The second parameter token of the query, another integer representing a statement number.
 * @param resultTable The table to be set as a truth table if the Follows relationship exists.
 */
void FollowsStrategy::processIntegerParams(
                                           std::shared_ptr<ResultTable> resultTable) {
    int firstStmtNum = std::stoi(firstParam.getValue());
    int secondStmtNum = std::stoi(secondParam.getValue());

    bool hasFollows = (variant == "Follows") ?
                      followsReader->hasFollows(firstStmtNum, secondStmtNum):
                      followsTReader->hasFollowsT(firstStmtNum, secondStmtNum);
    if (hasFollows) {
        resultTable->setAsTruthTable();
    }
}
