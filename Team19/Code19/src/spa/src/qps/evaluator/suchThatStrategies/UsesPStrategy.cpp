#pragma once
#include "qps/evaluator/suchThatStrategies/UsesPStrategy.h"

std::shared_ptr<ResultTable> UsesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult)
{
    auto resultTable = make_shared<ResultTable>();
    this->usesPReader = pkbReaderManager.getUsesPReader();


    const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
    const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();

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

void UsesPStrategy::processBothSynonyms(const Token &firstParam, const Token &secondParam,
                                            const ParsingResult &parsingResult,
                                            std::shared_ptr<ResultTable> resultTable,
                                            PKBReaderManager &pkbReaderManager) {
    // get the types of both synonyms
    string firstParamType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    string secondParamType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    insertColsToTable(firstParam, secondParam, resultTable);

    if (firstParamType == "procedure" || firstParamType == "call") {
        std::unordered_set<std::string> allProcs =
                pkbReaderManager.getUsesPReader()->getAllProcsThatUseAnyVariable();
        for (string proc : allProcs) {
            std::unordered_set<std::string> allVars =
                    pkbReaderManager.getUsesPReader()->getAllVariablesUsedByProc(proc);
            // copy the value of procs to a rvalue string
            pair<string, string> col1Pair = make_pair<string, string>(firstParam.getValue(), std::move(proc));
            for (string var : allVars) {
                pair<string, string> col2Pair = make_pair<string, string>(secondParam.getValue(), std::move(var));
                insertRowToTable(col1Pair, col2Pair, resultTable);
            }
        }
    }

}


void UsesPStrategy::processFirstParam(const Token &firstParam, const Token &secondParam,
                                          const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                          PKBReaderManager &pkbReaderManager) {
    string colName = firstParam.getValue();
    insertSingleColToTable(firstParam, resultTable);
    if (secondParam.getType() == TokenType::IDENT) {
        string secondParamValue = secondParam.getValue();
        std::unordered_set<std::string> allProcs = pkbReaderManager.getUsesPReader()->getAllProcsThatUseVariable(secondParamValue);
        for (string proc : allProcs) {
            pair<string, string> colPair = make_pair<string, string>(std::move(colName), std::move(proc));
            insertSingleColRowToTable(colPair, resultTable);
        }
    } else {
        // it is a wildcard
        std::unordered_set<std::string> allProcs = pkbReaderManager.getUsesPReader()->getAllProcsThatUseAnyVariable();
        for (string proc : allProcs) {
            pair<string, string> colPair = make_pair<string, string>(std::move(colName), std::move(proc));
            insertSingleColRowToTable(colPair, resultTable);
        }

    }
}

void UsesPStrategy::processSecondParam(const Token &firstParam, const Token &secondParam,
                                           const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                           PKBReaderManager &pkbReaderManager) {
    string colName = secondParam.getValue();
    if (firstParam.getType() == TokenType::IDENT) {
        string firstParamValue = firstParam.getValue();
        std::unordered_set<std::string> allVars = pkbReaderManager.getUsesPReader()->getAllVariablesUsedByProc(firstParamValue);
        for (string var : allVars) {
            pair<string, string> colPair = make_pair<string, string>(std::move(colName), std::move(var));
            insertSingleColRowToTable(colPair, resultTable);
        }
    } else {
        // it is a wildcard
        std::unordered_set<std::string> allVars = pkbReaderManager.getUsesPReader()->getAllVariablesUsedByAnyProc();
        for (string var : allVars) {
            pair<string, string> colPair = make_pair<string, string>(std::move(colName), std::move(var));
            insertSingleColRowToTable(colPair, resultTable);
        }
    }
}

void UsesPStrategy::processBothConstants(const Token &firstParam, const Token &secondParam,
                                             const ParsingResult &parsingResult,
                                             std::shared_ptr<ResultTable> resultTable, PKBReaderManager &pkbReaderManager) {
    if (isBothParamsWildcard(firstParam, secondParam)) {
        if (!pkbReaderManager.getUsesPReader()->getAllProcsThatUseAnyVariable().empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (firstParam.getType() == TokenType::Wildcard) {
        string secondParamValue = secondParam.getValue();
        if (!pkbReaderManager.getUsesPReader()->getRelationshipsByValue(secondParamValue).empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        string firstParamValue = firstParam.getValue();
        if (!pkbReaderManager.getUsesPReader()->getRelationshipsByKey(firstParamValue).empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        string firstParamValue = firstParam.getValue();
        string secondParamValue = secondParam.getValue();
        if (pkbReaderManager.getUsesPReader()->hasRelationship(firstParamValue, secondParamValue)) {
            resultTable->setAsTruthTable();
        }
    }
}