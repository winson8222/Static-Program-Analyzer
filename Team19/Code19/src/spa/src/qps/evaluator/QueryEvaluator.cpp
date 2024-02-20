#include "QueryEvaluator.h"
#include "qps/evaluator/suchThatStrategies/FollowsStrategy.h" // Include FollowsStrategy
#include "qps/evaluator/suchThatStrategies/ParentStrategy.h" // Include ParentStrategy
#include "qps/evaluator/suchThatStrategies/ModifiesStrategy.h" // Include ModifiesStrategy
#include "qps/evaluator/suchThatStrategies/UsesStrategy.h" // Include UsesStrategy
#include "PatternStrategy.h"
#include "qps/evaluator/ResultTable.h"


using namespace std;

QueryEvaluator::QueryEvaluator(std::shared_ptr<PKBReaderManager> pkbReaderManager, ParsingResult& parsingResult)
    : pkbReaderManager(pkbReaderManager), parsingResult(parsingResult) {}

void QueryEvaluator::addStrategy(std::unique_ptr<QueryEvaluationStrategy> strategy) {
    strategies.push_back(std::move(strategy));
}

std::vector<string> QueryEvaluator::evaluateQuery() {
    // if query is not valid, return error message and stop evaluation
    if (!parsingResult.isQueryValid()) {
        // convert error message to vector<string>
        vector<string> error;
        error.push_back(parsingResult.getErrorMessage());
        return error;
    }

    if (parsingResult.getSuchThatClauseRelationship().getValue() == "Follows" || parsingResult.getSuchThatClauseRelationship().getValue() == "Follows*") {
        addStrategy(std::make_unique<FollowsStrategy>());
    }
    else if (parsingResult.getSuchThatClauseRelationship().getValue() == "Parent" || parsingResult.getSuchThatClauseRelationship().getValue() == "ParentT") {
        addStrategy(std::make_unique<ParentStrategy>());
    }
    else if (parsingResult.getSuchThatClauseRelationship().getValue() == "Modifies") {
		addStrategy(std::make_unique<ModifiesStrategy>());
	}
    else if (parsingResult.getSuchThatClauseRelationship().getValue() == "Uses") {
        addStrategy(std::make_unique<UsesStrategy>());
    }
    else if (parsingResult.getPatternClauseRelationship().getValue() != "") {
        addStrategy(std::make_unique<PatternStrategy>());
    }
    else {
        // if there is no clause, return all statements
        /*
        unordered_set<int> allStmts = pkbReaderManager->getStatementReader()->getAllStatements();
        for (int stmt : allStmts) {
            result.insert(to_string(stmt));
        }
        */
    }

    bool isFirstStrategy = true;
    for (auto& strategy : strategies) {
        if (isFirstStrategy) {
            result = strategy->evaluateQuery(*pkbReaderManager, parsingResult);
            isFirstStrategy = false;
        }
        else {
            result = result->joinOnColumns(strategy->evaluateQuery(*pkbReaderManager, parsingResult));
        }
    }

    std::string requiredSynonym = parsingResult.getRequiredSynonym();
    std::string requiredType = parsingResult.getRequiredSynonymType();

    if (result->getColumnValues(requiredSynonym).empty()) {
        //return all statement/variables/whatever
        // return getAllEntities(requiredType);
        return;
    }
    else {
		return result->getColumnValues(requiredSynonym);
	}
 

}






