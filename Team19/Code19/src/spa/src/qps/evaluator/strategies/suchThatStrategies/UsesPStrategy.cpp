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
            insertRowsWithMatchedResults(firstParam, secondParam, proc, allVars, resultTable);
        }
    }

}


void UsesPStrategy::processFirstParam(const Token &firstParam, const Token &secondParam,
                                          const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                          PKBReaderManager &pkbReaderManager) {
    string colName = firstParam.getValue();
    insertSingleColToTable(firstParam, resultTable);
    std::unordered_set<std::string> allProcs;
    if (secondParam.getType() == TokenType::QuoutIDENT) {
        string secondParamValue = extractQuotedExpression(secondParam);
        allProcs = pkbReaderManager.getUsesPReader()->getAllProcsThatUseVariable(secondParamValue);

    } else {
        // it is a wildcard
        allProcs = pkbReaderManager.getUsesPReader()->getAllProcsThatUseAnyVariable();

    }
    insertRowsWithSingleColumn(colName, allProcs, resultTable);
}

void UsesPStrategy::processSecondParam(const Token &firstParam, const Token &secondParam,
                                           const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                           PKBReaderManager &pkbReaderManager) {
    string colName = secondParam.getValue();
    insertSingleColToTable(secondParam, resultTable);
    std::unordered_set<std::string> allVars;
    if (firstParam.getType() == TokenType::QuoutIDENT) {
        string firstParamValue = extractQuotedExpression(firstParam);
        allVars = pkbReaderManager.getUsesPReader()->getAllVariablesUsedByProc(firstParamValue);

    } else {
        // it is a wildcard
        allVars = pkbReaderManager.getUsesPReader()->getAllVariablesUsedByAnyProc();

    }
    insertRowsWithSingleColumn(colName, allVars, resultTable);
}

void UsesPStrategy::processBothConstants(const Token &firstParam, const Token &secondParam,
                                             const ParsingResult &parsingResult,
                                             std::shared_ptr<ResultTable> resultTable, PKBReaderManager &pkbReaderManager) {
    if (isBothParamsWildcard(firstParam, secondParam)) {
        if (!pkbReaderManager.getUsesPReader()->getAllProcsThatUseAnyVariable().empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(firstParam, secondParam, pkbReaderManager.getUsesPReader(), resultTable);
    }
}