#pragma once
#include "UsesPStrategy.h"

std::shared_ptr<ResultTable> UsesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = make_shared<ResultTable>();
    this->usesPReader = pkbReaderManager.getUsesPReader();



    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->firstParam = suchClause->getFirstParam();
    this->secondParam = suchClause->getSecondParam();

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

void UsesPStrategy::processBothSynonyms(const ParsingResult &parsingResult,
                                            std::shared_ptr<ResultTable> resultTable) {
    // get the types of both synonyms
    string firstParamType = parsingResult.getDeclaredSynonym(this->firstParam.getValue());
    string secondParamType = parsingResult.getDeclaredSynonym(secondParam.getValue());
    insertColsToTable(this->firstParam, secondParam, resultTable);

    if (firstParamType == "procedure") {
        std::unordered_set<std::string> allProcs =
                this->usesPReader->getAllProcsThatUseAnyVariable();
        for (string proc : allProcs) {
            std::unordered_set<std::string> allVars =
                    this->usesPReader->getAllVariablesUsedByProc(proc);
            // copy the value of procs to a rvalue string
            insertRowsWithMatchedResults(this->firstParam, secondParam, proc, allVars, resultTable);
        }
    }

}


void UsesPStrategy::processFirstParam(const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable) {
    string colName = this->firstParam.getValue();
    insertSingleColToTable(this->firstParam, resultTable);
    std::unordered_set<std::string> allProcs;
    if (secondParam.getType() == TokenType::QuoutIDENT) {
        string secondParamValue = extractQuotedExpression(secondParam);
        allProcs = this->usesPReader->getAllProcsThatUseVariable(secondParamValue);

    } else {
        // it is a wildcard
        allProcs = this->usesPReader->getAllProcsThatUseAnyVariable();

    }
    insertRowsWithSingleColumn(colName, allProcs, resultTable);
}

void UsesPStrategy::processSecondParam(const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable) {
    string colName = secondParam.getValue();
    insertSingleColToTable(secondParam, resultTable);
    std::unordered_set<std::string> allVars;
    if (this->firstParam.getType() == TokenType::QuoutIDENT) {
        string firstParamValue = extractQuotedExpression(this->firstParam);
        allVars = this->usesPReader->getAllVariablesUsedByProc(firstParamValue);

    } else {
        // it is a wildcard
        allVars = this->usesPReader->getAllVariablesUsedByAnyProc();

    }
    insertRowsWithSingleColumn(colName, allVars, resultTable);
}

void UsesPStrategy::processBothConstants(const ParsingResult &parsingResult,
                                             std::shared_ptr<ResultTable> resultTable) {
    if (isBothParamsWildcard(this->firstParam, secondParam)) {
        if (!this->usesPReader->getAllProcsThatUseAnyVariable().empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(this->firstParam, secondParam, this->usesPReader, resultTable);
    }
}