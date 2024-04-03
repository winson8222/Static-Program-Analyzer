#pragma once

#include <map>
#include <memory>
#include <variant>
#include <vector> // For storing multiple strategies
#include "qps/evaluator/QueryEvaluationStrategy.h" // Include the strategy interface
#include "qps/evaluator/ResultTable.h"
#include "qps/evaluator/strategies/suchThatStrategies/FollowsStrategy.h" // Include FollowsStrategy
#include "qps/evaluator/strategies/suchThatStrategies/ParentStrategy.h" // Include ParentStrategy
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesStrategy.h" // Include ModifiesStrategy
#include "qps/evaluator/strategies/suchThatStrategies/UsesStrategy.h" // Include UsesStrategy
#include "qps/evaluator/strategies/suchThatStrategies/UsesPStrategy.h" // Include UsesPStrategy
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesPStrategy.h" // Include ModifiesPStrategy
#include "qps/evaluator/strategies/suchThatStrategies/CallsStrategy.h" // Include CallsStrategy
#include "qps/evaluator/strategies/suchThatStrategies/NextStrategy.h" // Include NextStrategy
#include "qps/evaluator/strategies/suchThatStrategies/AffectsStrategy.h" // Include AffectsStrategy
#include "qps/evaluator/strategies/patternStrategies/AssignPatternStrategy.h" // Include AssignPatternStrategy
#include "qps/evaluator/strategies/patternStrategies/WhilePatternStrategy.h" // Include WhilePatternStrategy
#include "qps/evaluator/strategies/patternStrategies/IfPatternStrategy.h" // Include IfPatternStrategy
#include "qps/parser/Token.h"

class QueryEvaluator {
private:
    std::shared_ptr<PKBReaderManager> pkbReaderManager;
    std::shared_ptr<PKBCacheManager> pkbCacheManager;
    ParsingResult& parsingResult;
    std::shared_ptr<ResultTable> result;
    std::vector<std::unique_ptr<QueryEvaluationStrategy>> strategies; // Store multiple strategies
    std::map<std::string, std::function<std::unique_ptr<QueryEvaluationStrategy>(std::shared_ptr<Clause>)>>clauseToStrategiesMap;
    std::map<TokenType, std::function<std::unique_ptr<QueryEvaluationStrategy>()>> suchThatStrategyFactory; // Map of strategy factory
    std::map<std::string, std::function<std::unique_ptr<QueryEvaluationStrategy>()>> patternStrategyFactory; // Map of strategy factory
    std::map<std::string, std::function<std::variant<std::unordered_set<int>, std::unordered_set<std::string>>()>> entityFactory;
    std::vector<std::pair<std::unique_ptr<QueryEvaluationStrategy>, const Clause*>> strategyAndClausePairs;
    std::unordered_map<std::string, std::function<std::string(int)>> procNameMap;
    std::unordered_map<std::string, std::function<std::string(int)>> varNameMap;

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
    QueryEvaluator(std::shared_ptr<PKBReaderManager> pkbReaderManager, std::shared_ptr<PKBCacheManager> pkbCacheManager, ParsingResult& parsingResult);

	/**
	 * @brief Evaluates the query
	 * @return std::unordered_set<std::string> The result set
	 */
	std::unordered_set<std::string> evaluateQuery();

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

    /**
     * Populates a result table with all possible combinations of entities for two specified columns.
     *
     * This method dynamically determines the entity types for the specified columns based on the
     * ParsingResult. It then retrieves all entities for each type and generates a result table
     * containing every possible combination of these entities across the two columns.
     *
     * @param colA The name of the first column, which will contain entities of the first type.
     * @param colB The name of the second column, which will contain entities of the second type.
     * @param parsingResult The ParsingResult instance containing information about declared synonyms
     *                      and their types, which is used to determine the types of entities to retrieve.
     * @return A shared pointer to a ResultTable populated with all possible combinations of entities
     *         for the specified columns.
     */
    std::shared_ptr<ResultTable> populateEntityCombinations(const std::string& colA, const std::string& colB);

    void initializeStrategyFactory(); // Method to initialize the strategy factory
    void initializeEntityFactory(); // Method to initialize the entity factory
    std::string join(const std::unordered_set<std::string>& elements, const std::string& delimiter);
    std::string convertToAttr(const std::string& synonym , std::string ref);
    std::string convertToStmtNumber(std::string synonym , std::string ref);
    std::string convertToVarName(const std::string& synonym , std::string ref);
    std::string convertToProcName(const std::string& synonym , std::string ref);
    void convertToAttrSet(const std::string& synonym, std::unordered_set<std::string>& valueSet, std::unordered_set<std::string>& attrSet);
    std::vector<std::string> removeAllAttrRefs(const std::vector<std::string>& requiredSynonyms);
    std::vector<std::shared_ptr<Clause>> addAllClauses(ParsingResult& parsingResult);

    void initializeProcNameMap();
    void initializeVarNameMap();
    void throwNoSuchMethodException();
    bool handleTableTrue(std::shared_ptr<Clause> clause);
    bool handleTableFalse(std::shared_ptr<Clause> clause);
    void populateEntityCombinations(std::shared_ptr<ResultTable> table);
    std::shared_ptr<ResultTable> getInverse(std::shared_ptr<ResultTable>);
};
