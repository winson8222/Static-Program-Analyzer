#pragma once
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesPStrategy.h"

std::shared_ptr<ResultTable> ModifiesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = make_shared<ResultTable>();
    this->modifiesPReader = pkbReaderManager.getModifiesPReader();


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

void ModifiesPStrategy::processBothSynonyms(const Token &firstParam, const Token &secondParam,
                                            const ParsingResult &parsingResult,
                                            std::shared_ptr<ResultTable> resultTable,
                                            PKBReaderManager &pkbReaderManager) {
    // get the types of both synonyms
    string firstParamType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    string secondParamType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    insertColsToTable(firstParam, secondParam, resultTable);

    if (firstParamType == "procedure") {
        std::unordered_set<std::string> allProcs =
                pkbReaderManager.getModifiesPReader()->getAllProcsThatModifyAnyVariable();
        for (string proc : allProcs) {
            std::unordered_set<std::string> allVars =
                    pkbReaderManager.getModifiesPReader()->getAllVariablesModifiedByProc(proc);
            // copy the value of procs to a rvalue string
            insertRowsWithMatchedResults(firstParam, secondParam, proc, allVars, resultTable);
        }
    }

}


void ModifiesPStrategy::processFirstParam(const Token &firstParam, const Token &secondParam,
                                          const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                          PKBReaderManager &pkbReaderManager) {
    string colName = firstParam.getValue();
    insertSingleColToTable(firstParam, resultTable);
    std::unordered_set<std::string> allProcs;
    if (secondParam.getType() == TokenType::QuoutIDENT) {
        string secondParamValue = extractQuotedExpression(secondParam);

        allProcs = pkbReaderManager.getModifiesPReader()->getAllProcsThatModifyVariable(secondParamValue);

    } else {
        // it is a wildcard
        allProcs = pkbReaderManager.getModifiesPReader()->getAllProcsThatModifyAnyVariable();

    }
    insertRowsWithSingleColumn(colName, allProcs, resultTable);
}

void ModifiesPStrategy::processSecondParam(const Token &firstParam, const Token &secondParam,
                                           const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable,
                                           PKBReaderManager &pkbReaderManager) {
    string colName = secondParam.getValue();
    insertSingleColToTable(secondParam, resultTable);
    std::unordered_set<std::string> allVars;
    if (firstParam.getType() == TokenType::QuoutIDENT) {
        string firstParamValue = extractQuotedExpression(firstParam);
        allVars = pkbReaderManager.getModifiesPReader()->getAllVariablesModifiedByProc(firstParamValue);
    } else {
        // it is a wildcard
        allVars = pkbReaderManager.getModifiesPReader()->getAllVariablesModifiedByAnyProc();
    }
    insertRowsWithSingleColumn(colName, allVars, resultTable);
}

void ModifiesPStrategy::processBothConstants(const Token &firstParam, const Token &secondParam,
                                             const ParsingResult &parsingResult,
                                             std::shared_ptr<ResultTable> resultTable, PKBReaderManager &pkbReaderManager) {
    if (isBothParamsWildcard(firstParam, secondParam)) {
        if (!pkbReaderManager.getModifiesPReader()->getAllProcsThatModifyAnyVariable().empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(firstParam, secondParam, pkbReaderManager.getModifiesPReader(), resultTable);
    }

}