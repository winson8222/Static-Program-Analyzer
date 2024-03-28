#include "qps/evaluator/strategies/suchThatStrategies/CallsStrategy.h"

std::shared_ptr<ResultTable> CallsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = make_shared<ResultTable>();


    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->firstParam = suchClause->getFirstParam();
    this->secondParam = suchClause->getSecondParam();
    this-> variant = suchClause->getRelationship().getValue();

    if (this->variant == "Calls") {
        this->reader = pkbReaderManager.getCallsReader();
    } else {
        this->reader = pkbReaderManager.getCallsTReader();
    }

    if (isBothParamsSynonym(this->firstParam, this->secondParam)) {
        this->processBothSynonyms(parsingResult, resultTable);
    } else if (this->firstParam.getType() == TokenType::IDENT) {
        this->processFirstParam(parsingResult, resultTable);
    } else if (this->secondParam.getType() == TokenType::IDENT) {
        this->processSecondParam(parsingResult, resultTable);
    } else {
        this->processBothConstants(parsingResult, resultTable);
    }

    return resultTable;
}

void CallsStrategy::processBothSynonyms(const ParsingResult &parsingResult,
                                            std::shared_ptr<ResultTable> resultTable) {
    // get the types of both synonyms
    string firstParamType = parsingResult.getDeclaredSynonym(this->firstParam.getValue());
    string secondParamType = parsingResult.getDeclaredSynonym(this->secondParam.getValue());
    insertColsToTable(this->firstParam, this->secondParam, resultTable);
    unordered_set<string> allCallees;

    if (firstParamType == "procedure" && secondParamType == "procedure") {
        std::unordered_set<std::string> allProcs = this->reader->getKeys();
        for (string caller : allProcs) {
            allCallees = this->reader->getRelationshipsByKey(caller);
            insertRowsWithMatchedResults(this->firstParam, this->secondParam, caller, allCallees, resultTable);
        }
    }

}


void CallsStrategy::processFirstParam(const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable) {
    string colName = this->firstParam.getValue();
    insertSingleColToTable(this->firstParam, resultTable);
    std::unordered_set<std::string> allCallers;

    if (this->secondParam.getType() == TokenType::QuoutIDENT ) {
        string secondParamValue = extractQuotedExpression(this->secondParam);
        allCallers = this->reader->getRelationshipsByValue(secondParamValue);
    } else {
        // it is a wildcard
        allCallers = this->reader->getKeys();
    }
    insertRowsWithSingleColumn(colName, allCallers, resultTable);
}

void CallsStrategy::processSecondParam(const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable) {
    string colName = this->secondParam.getValue();
    insertSingleColToTable(this->secondParam, resultTable);
    std::unordered_set<std::string> allCallees;
    if (this->firstParam.getType() == TokenType::QuoutIDENT) {
        string firstParamValue = extractQuotedExpression(this->firstParam);
        allCallees = this->reader->getRelationshipsByKey(firstParamValue);
    } else {
        // it is a wildcard
        allCallees = this->reader->getValues();
    }
    insertRowsWithSingleColumn(colName, allCallees, resultTable);
}

void CallsStrategy::processBothConstants(const ParsingResult &parsingResult,
                                             std::shared_ptr<ResultTable> resultTable) {
    if (isBothParamsWildcard(this->firstParam, this->secondParam)) {
        if (!this->reader->isEmpty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(this->firstParam, this->secondParam, this->reader, resultTable);
    }

}
