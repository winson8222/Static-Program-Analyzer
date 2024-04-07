#include "UsesStrategy.h"
#include <memory>
#include <unordered_map>


std::shared_ptr<ResultTable> UsesStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                  const ParsingResult &parsingResult,
                                                                  const Clause &clause,
                                                                  std::shared_ptr<ResultTable> result) {
    setIntermediateResultTable(result);
    return evaluateQuery(pkbReaderManager, parsingResult, clause);
}


std::shared_ptr<ResultTable> UsesStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = std::make_shared<ResultTable>();
    this->usesSReader = pkbReaderManager.getUsesSReader();

    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    const Token& suchThatFirstParam = suchClause->getFirstParam();
    const Token& suchThatSecondParam = suchClause->getSecondParam();


    if (isBothParamsSynonym(suchThatFirstParam, suchThatSecondParam)) {
        processBothSynonyms(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
    } else if (suchThatFirstParam.getType() == TokenType::IDENT) {
        processFirstParam(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
    } else if (suchThatSecondParam.getType() == TokenType::IDENT) {
        processSecondParam(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
    } else {
        processBothConstants(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable);
    }
    return resultTable;
}

void UsesStrategy::processBothSynonyms(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult, 
    std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) 
{
    // get all statements that modifies a variable
    std::unordered_set<int> allModifiesStmts = usesSReader->getAllStmtsThatUseAnyVariable();
    // check what type of statement is the firstParam
    std::string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    // filter the statements that modifies the variable based on the stmt type
    std::unordered_set<int> allFilteredModifiesStmts;
    allFilteredModifiesStmts = getFilteredStmtsNumByType(allModifiesStmts,statementType, pkbReaderManager);

    // get all variables that are modified by a statement
    resultTable->addColumnsSet({firstParam.getValue(), secondParam.getValue()});
    for (int stmt: allFilteredModifiesStmts) {
        std::unordered_set<std::string> allModifiedVars = usesSReader->getAllVariablesUsedByStmt(stmt);
        for (const std::string &var: allModifiedVars) {
            std::unordered_map<std::string, std::string> row;
            row[firstParam.getValue()] = std::to_string(stmt);
            row[secondParam.getValue()] = var;
            resultTable->insertNewRow(row);
        }
    }
}

void UsesStrategy::processFirstParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
        ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) {
    // get all statements that modifies a variable
    std::unordered_set<int> allModifiesStmts;
    if (secondParam.getType() == TokenType::Wildcard) {
        allModifiesStmts = usesSReader->getAllStmtsThatUseAnyVariable();
    } else {
        std::string unquotedValue = extractQuotedExpression(secondParam);
        allModifiesStmts = usesSReader->getAllStmtsThatUseVariable(unquotedValue);
    }

    // check what type of statement is the firstParam
    std::string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    // filter the statements that modifies the variable based on the stmt type
    std::unordered_set<int> allFilteredModifiesStmts;
    allFilteredModifiesStmts = getFilteredStmtsNumByType(allModifiesStmts,statementType, pkbReaderManager);
    // need to be changed, now is just any call statements not filtered by the proc used

    // get all filtered statements that modifies the variable
    resultTable->insertColumn(firstParam.getValue());
    for (int stmt: allFilteredModifiesStmts) {
        std::unordered_map<std::string,std::string> newRow;
        newRow[firstParam.getValue()] = std::to_string(stmt);
        resultTable->insertNewRow(newRow);
    }
}


void UsesStrategy::processSecondParam(const Token &firstParam, const Token &secondParam,
                                          const ParsingResult &parsingResult,
                                          std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) {
    // get all variables that are modified by a statement
    std::unordered_set<std::string> allModifiedVars;
    if (firstParam.getType() == TokenType::Wildcard) {
        allModifiedVars = usesSReader->getAllVariablesUsedByAnyStmt();

    } else {
        allModifiedVars = usesSReader->getAllVariablesUsedByStmt(
                stoi(firstParam.getValue()));
    }

    // add to result
    resultTable->insertColumn(secondParam.getValue());
    for (const std::string &var: allModifiedVars) {
        std::unordered_map<std::string, std::string> newRow;
        newRow[secondParam.getValue()] = var;
        resultTable->insertNewRow(newRow);
    }
}

void UsesStrategy::processBothConstants(const Token &firstParam, const Token &secondParam,
                                            const ParsingResult &parsingResult,
                                            std::shared_ptr<ResultTable> resultTable) {
    // check if the statement modifies the variable
    if (isBothParamsWildcard(firstParam, secondParam)) {
        if (this->usesSReader->getAllStmtsThatUseAnyVariable().empty()) {
            resultTable->setAsTruthTable();
        }
    } else {
        setTrueIfRelationShipExist(firstParam, secondParam, this->usesSReader, resultTable);
    }
}
