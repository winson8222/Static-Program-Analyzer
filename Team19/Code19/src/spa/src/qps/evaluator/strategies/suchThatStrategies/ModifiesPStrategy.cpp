#pragma once
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesPStrategy.h"

std::shared_ptr<ResultTable> ModifiesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult)
{
    auto resultTable = make_shared<ResultTable>();
    this->modifiesPReader = pkbReaderManager.getModifiesPReader();


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

void ModifiesPStrategy::processBothSynonyms(const Token &firstParam, const Token &secondParam,
                                            const ParsingResult &parsingResult,
                                            std::shared_ptr<ResultTable> resultTable,
                                            PKBReaderManager &pkbReaderManager) {
    // get the types of both synonyms
    string firstParamType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    string secondParamType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    insertColsToTable(firstParam, secondParam, resultTable);

    if (firstParamType == "procedure" || firstParamType == "call") {
        std::unordered_set<std::string> allProcs =
                pkbReaderManager.getModifiesPReader()->getAllProcsThatModifyAnyVariable();
        for (string proc : allProcs) {
            std::unordered_set<std::string> allVars =
                    pkbReaderManager.getModifiesPReader()->getAllVariablesModifiedByProc(proc);
            // copy the value of procs to a rvalue string
            pair<string, string> col1Pair = make_pair<string, string>(firstParam.getValue(), std::move(proc));
            for (string var : allVars) {
                pair<string, string> col2Pair = make_pair<string, string>(secondParam.getValue(), std::move(var));
                insertRowToTable(col1Pair, col2Pair, resultTable);
            }
        }
    }

}


void ModifiesPStrategy::processFirstParam(const Token &firstParam, const Token &secondParam,
                                          const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                          PKBReaderManager &pkbReaderManager) {
    string colName = firstParam.getValue();
    insertSingleColToTable(firstParam, resultTable);
    if (secondParam.getType() == TokenType::IDENT) {
        string secondParamValue = secondParam.getValue();
        std::unordered_set<std::string> allProcs = pkbReaderManager.getModifiesPReader()->getAllProcsThatModifyVariable(secondParamValue);
        for (string proc : allProcs) {
            pair<string, string> colPair = make_pair<string, string>(std::move(colName), std::move(proc));
            insertSingleColRowToTable(colPair, resultTable);
        }
    } else {
        // it is a wildcard
        std::unordered_set<std::string> allProcs = pkbReaderManager.getModifiesPReader()->getAllProcsThatModifyAnyVariable();
        for (string proc : allProcs) {
            pair<string, string> colPair = make_pair<string, string>(std::move(colName), std::move(proc));
            insertSingleColRowToTable(colPair, resultTable);
        }

    }
}

void ModifiesPStrategy::processSecondParam(const Token &firstParam, const Token &secondParam,
                                           const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                           PKBReaderManager &pkbReaderManager) {
    string colName = secondParam.getValue();
    if (firstParam.getType() == TokenType::IDENT) {
        string firstParamValue = firstParam.getValue();
        std::unordered_set<std::string> allVars = pkbReaderManager.getModifiesPReader()->getAllVariablesModifiedByProc(firstParamValue);
        for (string var : allVars) {
            pair<string, string> colPair = make_pair<string, string>(std::move(colName), std::move(var));
            insertSingleColRowToTable(colPair, resultTable);
        }
    } else {
        // it is a wildcard
        std::unordered_set<std::string> allVars = pkbReaderManager.getModifiesPReader()->getAllVariablesModifiedByAnyProc();
        for (string var : allVars) {
            pair<string, string> colPair = make_pair<string, string>(std::move(colName), std::move(var));
            insertSingleColRowToTable(colPair, resultTable);
        }
    }
}

void ModifiesPStrategy::processBothConstants(const Token &firstParam, const Token &secondParam,
                                             const ParsingResult &parsingResult,
                                             std::shared_ptr<ResultTable> resultTable, PKBReaderManager &pkbReaderManager) {
    if (isBothParamsWildcard(firstParam, secondParam)) {
        if (!pkbReaderManager.getModifiesPReader()->getAllProcsThatModifyAnyVariable().empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (firstParam.getType() == TokenType::Wildcard) {
        string secondParamValue = secondParam.getValue();
        if (!pkbReaderManager.getModifiesPReader()->getRelationshipsByValue(secondParamValue).empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        string firstParamValue = firstParam.getValue();
        if (!pkbReaderManager.getModifiesPReader()->getRelationshipsByKey(firstParamValue).empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        string firstParamValue = firstParam.getValue();
        string secondParamValue = secondParam.getValue();
        if (pkbReaderManager.getModifiesPReader()->hasRelationship(firstParamValue, secondParamValue)) {
            resultTable->setAsTruthTable();
        }
    }
}