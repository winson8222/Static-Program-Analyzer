#pragma once
#include "qps/evaluator/strategies/suchThatStrategies/CallsStrategy.h"

std::shared_ptr<ResultTable> CallsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = make_shared<ResultTable>();
    this->callsPReader = pkbReaderManager.getCallsReader();
    this->callsTReader = pkbReaderManager.getCallsTReader();

    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->firstParam = suchClause->getFirstParam();
    this->secondParam = suchClause->getSecondParam();
    this-> variant = suchClause->getRelationship().getValue();

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
    if (this->variant == "Calls") {
        std::unordered_set<std::string> allCallers =
                this->callsPReader->getAllDirectCallers();
        for (string caller : allCallers) {
            // copy the value of procs to a rvalue string
            allCallees = this->callsPReader->getDirectlyCalledProcedures(caller);
            insertRowsWithMatchedResults(this->firstParam, this->secondParam, caller, allCallees, resultTable);
        }
    } else {
        std::unordered_set<std::string> allCallers =
                this->callsTReader->getAllTransitiveCallers();
        for (string caller : allCallers) {
            // copy the value of procs to a rvalue string
            allCallees = this->callsTReader -> getTransitivelyCalledProcedures(caller);
            insertRowsWithMatchedResults(this->firstParam, this->secondParam, caller, allCallees, resultTable);
        }
    }


}


void CallsStrategy::processFirstParam(const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable) {
    string colName = this->firstParam.getValue();
    insertSingleColToTable(this->firstParam, resultTable);
    std::unordered_set<std::string> allCallers;
    if (this->variant == "Calls"){
        if (this->secondParam.getType() == TokenType::QuoutIDENT) {
            string secondParamValue = extractQuotedExpression(this->secondParam);

            allCallers = this->callsPReader->getDirectCallersOfProcedure(secondParamValue);

        } else {
            // it is a wildcard
            allCallers = this->callsPReader->getAllDirectCallers();


        }
    } else {
        if (this->secondParam.getType() == TokenType::QuoutIDENT) {
            string secondParamValue = extractQuotedExpression(this->secondParam);

            allCallers = this->callsTReader->getTransitiveCallersOfProcedure(secondParamValue);

        } else {
            // it is a wildcard
            allCallers = this->callsTReader->getAllTransitiveCallers();

        }

    }
    insertRowsWithSingleColumn(colName, allCallers, resultTable);

}

void CallsStrategy::processSecondParam(const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable) {
    string colName = this->secondParam.getValue();
    insertSingleColToTable(this->secondParam, resultTable);
    std::unordered_set<std::string> allCallees;
    if (this->variant == "Calls"){
        if (this->firstParam.getType() == TokenType::QuoutIDENT) {
            string firstParamValue = extractQuotedExpression(this->firstParam);
            allCallees = this->callsPReader->getDirectlyCalledProcedures(firstParamValue);
        } else {
            // it is a wildcard
            allCallees = this->callsPReader-> getAllDirectCallees();
        }
    } else {
        if (this->firstParam.getType() == TokenType::QuoutIDENT) {
            string firstParamValue = extractQuotedExpression(this->firstParam);
            allCallees = this->callsTReader->getTransitivelyCalledProcedures(firstParamValue);
        } else {
            // it is a wildcard
            allCallees = this->callsTReader->getAllTransitiveCallees();
        }
    }
    insertRowsWithSingleColumn(colName, allCallees, resultTable);
}

void CallsStrategy::processBothConstants(const ParsingResult &parsingResult,
                                             std::shared_ptr<ResultTable> resultTable) {
    if (this->variant == "Calls"){
        if (isBothParamsWildcard(this->firstParam, this->secondParam)) {
            if (!this->callsPReader->getAllDirectCallers().empty()) {
                resultTable->setAsTruthTable();
            }
        } else {
            setTrueIfRelationShipExist(this->firstParam, this->secondParam, this->callsPReader, resultTable);
        }
    } else {
        if (isBothParamsWildcard(this->firstParam, this->secondParam)) {
            if (!this->callsTReader->getAllTransitiveCallers().empty()) {
                resultTable->setAsTruthTable();
            }
        } else {
            setTrueIfRelationShipExist(this->firstParam, this->secondParam, this->callsTReader, resultTable);
        }
    }

}