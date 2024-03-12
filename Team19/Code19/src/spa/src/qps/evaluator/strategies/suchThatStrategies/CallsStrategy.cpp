#pragma once
#include "qps/evaluator/strategies/suchThatStrategies/CallsStrategy.h"

std::shared_ptr<ResultTable> CallsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = make_shared<ResultTable>();
    this->callsPReader = pkbReaderManager.getCallsReader();


    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    const Token& suchThatFirstParam = suchClause->getFirstParam();
    const Token& suchThatSecondParam = suchClause->getSecondParam();
    this-> variant = suchClause->getRelationship().getValue();

    if (isBothParamsSynonym(suchThatFirstParam, suchThatSecondParam)) {
        this->processBothSynonyms(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
    } else if (suchThatFirstParam.getType() == TokenType::IDENT) {
        this->processFirstParam(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
    } else if (suchThatSecondParam.getType() == TokenType::IDENT) {
        this->processSecondParam(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
    } else {
        this->processBothConstants(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
    }

    return resultTable;
}

void CallsStrategy::processBothSynonyms(const Token &firstParam, const Token &secondParam,
                                            const ParsingResult &parsingResult,
                                            std::shared_ptr<ResultTable> resultTable,
                                            PKBReaderManager &pkbReaderManager) {
    // get the types of both synonyms
    string firstParamType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    string secondParamType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    insertColsToTable(firstParam, secondParam, resultTable);
    unordered_set<string> allCallees;
    if (this->variant == "Calls") {
        std::unordered_set<std::string> allCallers =
                pkbReaderManager.getCallsReader()->getAllDirectCallers();
        for (string caller : allCallers) {
            // copy the value of procs to a rvalue string
            allCallees = pkbReaderManager.getCallsReader()->getDirectlyCalledProcedures(caller);
            insertRowsWithMatchedResults(firstParam, secondParam, caller, allCallees, resultTable);
        }
    } else {
        std::unordered_set<std::string> allCallers =
                pkbReaderManager.getCallsTReader()->getAllTransitiveCallers();
        for (string caller : allCallers) {
            // copy the value of procs to a rvalue string
            allCallees = pkbReaderManager.getCallsTReader() -> getTransitivelyCalledProcedures(caller);
            insertRowsWithMatchedResults(firstParam, secondParam, caller, allCallees, resultTable);
        }
    }


}


void CallsStrategy::processFirstParam(const Token &firstParam, const Token &secondParam,
                                          const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                          PKBReaderManager &pkbReaderManager) {
    string colName = firstParam.getValue();
    insertSingleColToTable(firstParam, resultTable);
    std::unordered_set<std::string> allCallers;
    if (this->variant == "Calls"){
        if (secondParam.getType() == TokenType::QuoutIDENT) {
            string secondParamValue = extractQuotedExpression(secondParam);

            allCallers = pkbReaderManager.getCallsReader()->getDirectCallersOfProcedure(secondParamValue);

        } else {
            // it is a wildcard
            allCallers = pkbReaderManager.getCallsReader()->getAllDirectCallers();


        }
    } else {
        if (secondParam.getType() == TokenType::QuoutIDENT) {
            string secondParamValue = extractQuotedExpression(secondParam);

            allCallers = pkbReaderManager.getCallsTReader()->getTransitiveCallersOfProcedure(secondParamValue);

        } else {
            // it is a wildcard
            allCallers = pkbReaderManager.getCallsTReader()->getAllTransitiveCallers();

        }

    }
    insertRowsWithSingleColumn(colName, allCallers, resultTable);

}

void CallsStrategy::processSecondParam(const Token &firstParam, const Token &secondParam,
                                           const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                           PKBReaderManager &pkbReaderManager) {
    string colName = secondParam.getValue();
    insertSingleColToTable(secondParam, resultTable);
    std::unordered_set<std::string> allCallees;
    if (this->variant == "Calls"){
        if (firstParam.getType() == TokenType::QuoutIDENT) {
            string firstParamValue = extractQuotedExpression(firstParam);
            allCallees = pkbReaderManager.getCallsReader()->getDirectlyCalledProcedures(firstParamValue);
        } else {
            // it is a wildcard
            allCallees = pkbReaderManager.getCallsReader()-> getAllDirectCallees();
        }
    } else {
        if (firstParam.getType() == TokenType::QuoutIDENT) {
            string firstParamValue = extractQuotedExpression(firstParam);
            allCallees = pkbReaderManager.getCallsTReader()->getTransitivelyCalledProcedures(firstParamValue);
        } else {
            // it is a wildcard
            allCallees = pkbReaderManager.getCallsTReader()->getAllTransitiveCallees();
        }
    }
    insertRowsWithSingleColumn(colName, allCallees, resultTable);
}

void CallsStrategy::processBothConstants(const Token &firstParam, const Token &secondParam,
                                             const ParsingResult &parsingResult,
                                             std::shared_ptr<ResultTable> resultTable, PKBReaderManager &pkbReaderManager) {
    if (this->variant == "Calls"){
        if (isBothParamsWildcard(firstParam, secondParam)) {
            if (!pkbReaderManager.getCallsReader()->getAllDirectCallers().empty()) {
                resultTable->setAsTruthTable();
            }
        } else {
            setTrueIfRelationShipExist(firstParam, secondParam, pkbReaderManager.getCallsReader(), resultTable);
        }
    } else {
        if (isBothParamsWildcard(firstParam, secondParam)) {
            if (!pkbReaderManager.getCallsTReader()->getAllTransitiveCallers().empty()) {
                resultTable->setAsTruthTable();
            }
        } else {
            setTrueIfRelationShipExist(firstParam, secondParam, pkbReaderManager.getCallsTReader(), resultTable);
        }
    }

}