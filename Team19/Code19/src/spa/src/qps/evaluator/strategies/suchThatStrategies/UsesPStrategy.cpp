#pragma once
#include "UsesPStrategy.h"

std::shared_ptr<ResultTable> UsesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = make_shared<ResultTable>();
    this->usesPReader = pkbReaderManager.getUsesPReader();


    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    const Token& suchThatFirstParam = suchClause->getFirstParam();
    const Token& suchThatSecondParam = suchClause->getSecondParam();

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

    if (firstParamType == "procedure") {
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
    if (secondParam.getType() == TokenType::QuoutIDENT) {
        string secondParamValue = extractQuotedExpression(secondParam);
        std::unordered_set<std::string> allProcs = pkbReaderManager.getUsesPReader()->getAllProcsThatUseVariable(secondParamValue);
        for (string proc : allProcs) {
            pair<string, string> colPair = make_pair(colName, std::move(proc));
            insertSingleColRowToTable(colPair, resultTable);
        }
    } else {
        // it is a wildcard
        std::unordered_set<std::string> allProcs = pkbReaderManager.getUsesPReader()->getAllProcsThatUseAnyVariable();
        for (string proc : allProcs) {
            pair<string, string> colPair = make_pair(colName, std::move(proc));
            insertSingleColRowToTable(colPair, resultTable);
        }

    }
}

void UsesPStrategy::processSecondParam(const Token &firstParam, const Token &secondParam,
                                           const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                           PKBReaderManager &pkbReaderManager) {
    string colName = secondParam.getValue();
    insertSingleColToTable(secondParam, resultTable);
    if (firstParam.getType() == TokenType::QuoutIDENT) {
        string firstParamValue = extractQuotedExpression(firstParam);
        std::unordered_set<std::string> allVars = pkbReaderManager.getUsesPReader()->getAllVariablesUsedByProc(firstParamValue);
        for (string var : allVars) {
            pair<string, string> colPair = make_pair(colName, std::move(var));
            insertSingleColRowToTable(colPair, resultTable);
        }
    } else {
        // it is a wildcard
        std::unordered_set<std::string> allVars = pkbReaderManager.getUsesPReader()->getAllVariablesUsedByAnyProc();
        for (string var : allVars) {
            pair<string, string> colPair = make_pair(colName, std::move(var));
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
        string secondParamValue = extractQuotedExpression(secondParam);
        if (!pkbReaderManager.getUsesPReader()->getRelationshipsByValue(secondParamValue).empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        string firstParamValue = extractQuotedExpression(firstParam);
        if (!pkbReaderManager.getUsesPReader()->getRelationshipsByKey(firstParamValue).empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        string firstParamValue = extractQuotedExpression(firstParam);
        string secondParamValue = extractQuotedExpression(secondParam);
        if (pkbReaderManager.getUsesPReader()->hasRelationship(firstParamValue, secondParamValue)) {
            resultTable->setAsTruthTable();
        }
    }
}