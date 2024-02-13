#include "QueryEvaluator.h"
#include "FollowsStrategy.h" // Include FollowsStrategy

using namespace std;

QueryEvaluator::QueryEvaluator(std::shared_ptr<PKBReaderManager> pkbReaderManager, ParsingResult& parsingResult)
    : pkbReaderManager(pkbReaderManager), parsingResult(parsingResult) {}

void QueryEvaluator::addStrategy(std::unique_ptr<QueryEvaluationStrategy> strategy) {
    strategies.push_back(std::move(strategy));
}

std::vector<string> QueryEvaluator::evaluateQuery() {
    std::string requiredSynonym = parsingResult.getRequiredSynonym();
    std::string requiredType = parsingResult.getRequiredSynonymType();

    if (requiredType == "stmt") {
        // For 'Follows' type, add FollowsStrategy
        if (parsingResult.getSuchThatClauseRelationship().getValue() == "Follows") {
            addStrategy(std::make_unique<FollowsStrategy>());
        }
        // Add other strategies based on requiredType
        // ...
    }

    if (requiredType == "variable") {
        // now we are only supporting getting all variables
        std::shared_ptr<VariableReader> variableReader = pkbReaderManager->getVariableReader();
        result = variableReader->getAllVariables();
    }

    for (auto& strategy : strategies) {
        std::unordered_set<std::string> strategyResult = strategy->evaluateQuery(*pkbReaderManager, parsingResult);
        combineResults(strategyResult);
    }

    return std::vector<std::string>(result.begin(), result.end());

}

/**
* Modifies the 'result' set to contain only elements that are also present in 'newResult'.
* This function effectively computes the intersection of 'result' and 'newResult'.
*
* @param newResult The set with which the intersection is to be found.
*/
void QueryEvaluator::combineResults(const std::unordered_set<std::string>& newResult) {
    for (auto it = result.begin(); it != result.end(); ) {
        if (newResult.find(*it) == newResult.end()) {
            it = result.erase(it);
        }
        else {
            ++it;
        }
    }
}





