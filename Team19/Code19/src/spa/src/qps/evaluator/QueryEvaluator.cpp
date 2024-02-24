#include "QueryEvaluator.h"
#include "PatternStrategy.h"
#include "qps/evaluator/ResultTable.h"


using namespace std;

QueryEvaluator::QueryEvaluator(std::shared_ptr<PKBReaderManager> pkbReaderManager, ParsingResult& parsingResult)
    : pkbReaderManager(pkbReaderManager), parsingResult(parsingResult) {
    initializeStrategyFactory();
}

void QueryEvaluator::addStrategy(std::unique_ptr<QueryEvaluationStrategy> strategy) {
    strategies.push_back(std::move(strategy));
}

std::vector<string> QueryEvaluator::evaluateQuery() {

    // create result table
    result = std::make_shared<ResultTable>();

    // if query is not valid, return error message and stop evaluation
    if (!parsingResult.isQueryValid()) {
        // convert error message to vector<string>
        vector<string> error;
        error.push_back(parsingResult.getErrorMessage());
        return error;
    }
    
    // Handle SuchThatClause relationships
    std::string suchThatRelationship = parsingResult.getSuchThatClauseRelationship().getValue();
    auto it = strategyFactory.find(suchThatRelationship);
    if (it != strategyFactory.end()) {
        addStrategy(it->second());
    }

    // Handle PatternClause
    if (!parsingResult.getPatternClauseRelationship().getValue().empty()) {
        addStrategy(std::make_unique<PatternStrategy>());
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

    if (result->hasColumn(requiredSynonym)) {
        return result->getColumnValues(requiredSynonym);
    }
    else {
        //return all statement/variables/whatever
        return getAllEntities(requiredType);
	}
 

}

std::vector<std::string> QueryEvaluator::getAllEntities(const std::string& requiredType) {
    std::vector<std::string> entities;

    if (requiredType == "assign") {
        auto assignEntities = pkbReaderManager->getAssignReader()->getAllEntities();
        for (int stmtNum : assignEntities) {
            entities.push_back(std::to_string(stmtNum));
        }
    }
    else if (requiredType == "call") {
        auto callEntities = pkbReaderManager->getCallReader()->getAllEntities();
        for (int stmtNum : callEntities) {
            entities.push_back(std::to_string(stmtNum));
        }
    }
    else if (requiredType == "constant") {
        auto constantEntities = pkbReaderManager->getConstantReader()->getAllEntities();
        for (int constant : constantEntities) {
            entities.push_back(std::to_string(constant));
        }
    }
    else if (requiredType == "if") {
        auto ifEntities = pkbReaderManager->getIfReader()->getAllEntities();
        for (int stmtNum : ifEntities) {
            entities.push_back(std::to_string(stmtNum));
        }
    }
    else if (requiredType == "print") {
        auto printEntities = pkbReaderManager->getPrintReader()->getAllEntities();
        for (int stmtNum : printEntities) {
            entities.push_back(std::to_string(stmtNum));
        }
    }
    else if (requiredType == "read") {
        auto readEntities = pkbReaderManager->getReadReader()->getAllEntities();
        for (int stmtNum : readEntities) {
            entities.push_back(std::to_string(stmtNum));
        }
    }
    else if (requiredType == "stmt") {
        auto statementEntities = pkbReaderManager->getStatementReader()->getAllEntities();
        for (int stmtNum : statementEntities) {
            entities.push_back(std::to_string(stmtNum));
        }
    }
    else if (requiredType == "variable") {
        auto variableEntities = pkbReaderManager->getVariableReader()->getAllEntities();
        for (const std::string& variable : variableEntities) {
            entities.push_back(variable);
        }
    }
    else if (requiredType == "while") {
        auto whileEntities = pkbReaderManager->getWhileReader()->getAllEntities();
        for (int stmtNum : whileEntities) {
            entities.push_back(std::to_string(stmtNum));
        }
    }
    else {
        //  throw an exception
        throw "Unknown type of entity required";
    }

    return entities;
}


