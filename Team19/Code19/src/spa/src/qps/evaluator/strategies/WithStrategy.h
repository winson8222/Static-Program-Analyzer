#pragma once // Ensures the file is included only once during compilation

#include "qps/evaluator/strategies/suchThatStrategies/StmtStmtStrategy.h"
#include <memory> // For std::shared_ptr


/**
 * @file WithStrategy.h
 * @brief Defines the WithStrategy class that implements equality between attributes.
 *
 * The WithStrategy class extends QueryEvaluationStrategy to evaluate queries 
 */

class WithStrategy : public QueryEvaluationStrategy {
private:
    Token firstParam;
    Token secondParam;
    ParsingResult parsingResult;

    /**
     * Retrieves the entities from the result table based on the given synonym and entity reader for integer entities.
     * @param synonym The synonym to retrieve the entities for.
     * @param resultTable The result table to retrieve the entities from.
     * @param entityReader The entity reader to use for retrieving the entities.
     * @return The set of entities retrieved from the result table.
     */
    std::unordered_set<std::string> retrieveIntEntities(std::string synonym, const std::shared_ptr<ResultTable>& resultTable, const std::shared_ptr<IEntityReader<int>>& entityReader);

    /**
     * Retrieves the entities from the result table based on the given synonym and entity reader for string entities.
     * @param synonym The synonym to retrieve the entities for.
     * @param resultTable The result table to retrieve the entities from.
     * @param entityReader The entity reader to use for retrieving the entities.
     * @return The set of entities retrieved from the result table.
     */
    std::unordered_set<std::string> retrieveStringEntities(std::string synonym, const std::shared_ptr<ResultTable>& resultTable, const std::shared_ptr<IEntityReader<std::string>>& entityReader);

    /**
     * Retrieves the links from the result table based on the given synonym and link reader for integer to string links.
     * @param synonym The synonym to retrieve the links for.
     * @param resultTable The result table to retrieve the links from.
     * @param linkReader The link reader to use for retrieving the links.
     * @return The set of links retrieved from the result table.
     */
    std::unordered_set<std::string> retrieveIntStringLinks(std::string synonym, const std::shared_ptr<ResultTable>& resultTable, const std::shared_ptr<ILinkReader<int, std::string>> linkReader);
public:
    /**
     * Evaluates a query based on the with clause.
     * @param pkbReaderManager Reference to the PKB reader manager for accessing program knowledge.
     * @param parsingResult The parsing result containing the details of the query.
     * @return A shared pointer to the result table generated by the evaluation.
     */
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, const std::shared_ptr<ResultTable>& originalResultTable) override;
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;


    /**
     * Processes queries where the first parameter is a synonym and the second parameter is specific.
     * @param pkbReaderManager Reference to the PKB reader manager for accessing program knowledge.
     * @param parsingResult The parsing result containing the details of the query.
     */
    std::unordered_set<std::string> processParam(Token param, PKBReaderManager& pkbReaderManager, const std::shared_ptr<ResultTable>& resultTable);


    pair<string, string> extractAttributes(Token param, PKBReaderManager& pkbReaderManager);
    bool isInteger(const std::string& str);
    bool isQuotedString(const std::string& str);

    std::vector<std::string> findIntersection(const std::unordered_set<std::string>& set1, const std::unordered_set<std::string>& set2);

    bool isIntegerStored(string synyonymType, string attribute);
    vector<std::string> mapStringSetToIntSet(PKBReaderManager& pkbReaderManager, const vector<string>& stringSet, string& synonymType);
    std::vector<pair<string, string>> populateResultTable(const std::shared_ptr<ResultTable>& resultTable, const std::vector<std::string>& intersection, Token param, PKBReaderManager& pkbReaderManager);
    
};
