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
    const Token& firstParam = suchClause->getFirstParam();
    const Token& secondParam = suchClause->getSecondParam();
    string variant = suchClause->getRelationship().getValue();

    // Handling different parameter types for the Follows relationship
    if (firstParam.getType() == TokenType::IDENT && secondParam.getType() == TokenType::IDENT) {
        processSynonyms(firstParam, secondParam, variant, resultTable, parsingResult, pkbReaderManager);
    } else if (firstParam.getType() == TokenType::IDENT) {
        processFirstParam(firstParam, secondParam, variant, resultTable, parsingResult, pkbReaderManager);
    } else if (secondParam.getType() == TokenType::IDENT) {
        processSecondParam(firstParam, secondParam, variant, resultTable, parsingResult, pkbReaderManager);
    } else if (isBothParamsWildcard(firstParam, secondParam)) {
        resultTable->setAsTruthTable(); // Handling wildcard cases
    } else if (isBothParamsInteger(firstParam, secondParam)) {
        processIntegerParams(firstParam, secondParam, resultTable); // Handling integer cases
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
void FollowsStrategy::processSynonyms(const Token& firstParam, const Token& secondParam, const std::string& variant, std::shared_ptr<ResultTable> resultTable,
                                      const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) {
    std::string col1 = firstParam.getValue();
    std::string col2 = secondParam.getValue();

    // check if the same synonym is being referred to
    if (col1 == col2) {
        resultTable->insertAllColumns({col1});
    } else {
        resultTable->insertAllColumns({col1, col2});
    }

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
            if (col1 == col2) {
                if (stmt1 == stmt2) {
                    resultTable->insertNewRow({{col1, std::to_string(stmt1)}});
                }
            } else {
                unordered_map<string, string> row;
                row[col1] = to_string(stmt1);
                row[col2] = to_string(stmt2);
                resultTable->insertNewRow(row);
            }

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
void FollowsStrategy::processFirstParam(const Token& firstParam, const Token& secondParam, const string& variant,
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
void FollowsStrategy::processSecondParam(const Token& firstParam, const Token& secondParam, const string& variant,
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
void FollowsStrategy::processIntegerParams(const Token& firstParam, const Token& secondParam,
                                           std::shared_ptr<ResultTable> resultTable) {
    int firstStmtNum = std::stoi(firstParam.getValue());
    int secondStmtNum = std::stoi(secondParam.getValue());

    if (followsReader->hasFollows(firstStmtNum, secondStmtNum)) {
        resultTable->setAsTruthTable();
    }
}
