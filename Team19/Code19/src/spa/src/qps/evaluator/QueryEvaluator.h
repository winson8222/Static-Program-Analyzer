#pragma once

#include <vector> // For storing multiple strategies
#include <memory>
#include <map>
#include "QueryEvaluationStrategy.h" // Include the strategy interface
#include "qps/evaluator/ResultTable.h"
#include "qps/parser/Token.h"
#include "qps/evaluator/strategies/suchThatStrategies/FollowsStrategy.h" // Include FollowsStrategy
#include "qps/evaluator/strategies/suchThatStrategies/ParentStrategy.h" // Include ParentStrategy
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesStrategy.h" // Include ModifiesStrategy
#include "qps/evaluator/strategies/suchThatStrategies/UsesStrategy.h" // Include UsesStrategy
#include "qps/evaluator/strategies/suchThatStrategies/UsesPStrategy.h" // Include UsesPStrategy
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesPStrategy.h" // Include ModifiesPStrategy
#include "qps/evaluator/strategies/suchThatStrategies/CallsStrategy.h" // Include CallsStrategy
#include <variant>


class QueryEvaluator {
private:
    std::shared_ptr<PKBReaderManager> pkbReaderManager;
    ParsingResult& parsingResult;
    std::shared_ptr<ResultTable> result;
    std::vector<std::unique_ptr<QueryEvaluationStrategy>> strategies; // Store multiple strategies
    std::map<TokenType, std::function<std::unique_ptr<QueryEvaluationStrategy>()>> strategyFactory; // Map of strategy factory
    std::map<std::string, std::function<std::variant<std::unordered_set<int>, std::unordered_set<std::string>>()>> entityFactory;
    std::vector<std::pair<std::unique_ptr<QueryEvaluationStrategy>, const Clause*>> strategyAndClausePairs;

	/**
	 * @brief Handles multiple return values in select clause
	 * @param finalSet The final set to be added to
	 * @param requiredSynonyms The required synonyms
	 */
	void evaluateMultipleReturnValues(std::unordered_set<std::string>& finalSet, std::vector<std::string> requiredSynonyms);
	/**
	 * @brief Construct the Entry String object to be added into the final set
	 * @param entry
	 * @param synonym
	 * @param map
	 */
	void constructEntryString(std::string& entry, std::string& synonym, std::unordered_map<std::string, std::string>& map);

	/**
	 * @brief Adds entries to the final set if none of the synonyms are in the result table
	 * @param finalSet The final set to be added to
	 * @param requiredSynonyms The required synonyms
	 * @param crossJoinMap The cross join map
	 */
	void addEntriesToFinalWithOnlyCrossJoin(std::unordered_set<std::string>& finalSet, std::vector<std::string> requiredSynonyms, std::unordered_map<std::string, std::string> crossJoinMap);

	/**
	 * @brief Adds entries to the final set if there are synonyms in the result table and
	 * some of the synonyms are in the cross join map
	 * @param finalSet The final set to be added to
	 * @param requiredSynonyms The required synonyms
	 * @param crossJoinMap The cross join map
	 */
	void addEntriesToFinalWithCrossJoinAndResult(std::unordered_set<std::string>& finalSet, std::vector<std::string> requiredSynonyms, std::unordered_map<std::string, std::string> crossJoinMap);

	/**
	 * @brief Adds entries to the final set if there are synonyms in the result table and
	 * none of the synonyms are in the cross join map
	 * @param finalSet The final set to be added to
	 * @param requiredSynonyms The required synonyms
	 */
	void addEntriesToFinalWithResultOnly(std::unordered_set<std::string>& finalSet, std::vector<std::string> requiredSynonyms);

	/**
	 * @brief Constructs the cross join map list for required synonyms not in the result table
	 * @param requiredSynonyms The required synonyms
	 * @return std::vector<std::unordered_map<std::string, std::string>> The cross join map list
	 */
	std::vector<std::unordered_map<std::string, std::string>> getCrossJoinMapList(std::vector<std::string> requiredSynonyms);
public:
    QueryEvaluator(std::shared_ptr<PKBReaderManager> pkbReaderManager, ParsingResult& parsingResult);

	/**
	 * @brief Evaluates the query
	 * @return std::unordered_set<std::string> The result set
	 */
	std::unordered_set<string> evaluateQuery();

	/**
	 * @brief Gets all the entities of a required type from the PKB
	 * @param requiredType The required type
	 * @return std::unordered_set<std::string> The set of entities
	 */
    std::unordered_set<std::string> getAllEntities(const std::string& requiredType);

	/**
	 * @brief Adds a strategy to the strategy factory
	 * @param strategy The strategy to be added
	 */
    void addStrategy(std::unique_ptr<QueryEvaluationStrategy> strategy); // Method to add strategies
    void initializeStrategyFactory(); // Method to initialize the strategy factory
    void initializeEntityFactory(); // Method to initialize the entity factory
    string join(const unordered_set<string>& elements, const string& delimiter);
};
