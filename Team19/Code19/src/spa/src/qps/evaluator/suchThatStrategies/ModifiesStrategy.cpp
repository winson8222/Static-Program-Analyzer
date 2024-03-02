#include "ModifiesStrategy.h"

std::shared_ptr<ResultTable> ModifiesStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = make_shared<ResultTable>();
    this->modifiesSReader= pkbReaderManager.getModifiesSReader();


    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    const Token& suchThatFirstParam = suchClause->firstParam;
    const Token& suchThatSecondParam = suchClause->secondParam;

    if (suchThatFirstParam.getType() == TokenType::IDENT && suchThatSecondParam.getType() == TokenType::IDENT) {
        processBothSynonyms(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
    } else if (suchThatFirstParam.getType() == TokenType::IDENT) {
        processFirstParam(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
    } else if (suchThatSecondParam.getType() == TokenType::IDENT) {
        processSecondParam(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable, pkbReaderManager);
    } else if (suchThatFirstParam.getType() == TokenType::INTEGER  && suchThatSecondParam.getType() == TokenType::QuoutIDENT) {
        processBothConstants(suchThatFirstParam, suchThatSecondParam, parsingResult, resultTable);
    } else if (suchThatFirstParam.getType() == TokenType::Wildcard || suchThatSecondParam.getType() == TokenType::Wildcard) {
        processWildCards(suchThatFirstParam, suchThatSecondParam, resultTable);
    } else {
        throw "Invalid Query!";
    }
    return resultTable;
}

void ModifiesStrategy::processBothSynonyms(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
                                           ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) {
    // get all statements that modifies a variable
    std::unordered_set<int> allModifiesStmts = modifiesSReader
            ->getAllStmtsThatModifyAnyVariable();
    // check what type of statement is the firstParam
    string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    // filter the statements that modifies the variable based on the stmt type
    std::unordered_set<int> allFilteredModifiesStmts;
    allFilteredModifiesStmts = getFilteredStmtsNumByType(allModifiesStmts, statementType, pkbReaderManager);

    // get all variables that are modified by a statement
    resultTable->addColumnsSet({firstParam.getValue(), secondParam.getValue()});
    for (int stmt: allFilteredModifiesStmts) {
        std::unordered_set<std::string> allModifiedVars = modifiesSReader
                ->getAllVariablesModifiedByStmt(stmt);
        for (const std::string &var: allModifiedVars) {
            std::unordered_map<std::string, std::string> row;
            row[firstParam.getValue()] = std::to_string(stmt);
            row[secondParam.getValue()] = var;
            resultTable->insertNewRow(row);
        }
    }
}

void ModifiesStrategy::processFirstParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
                                         ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) {
    // get all statements that modifies a variable
    std::unordered_set<int> allModifiesStmts;
    if (secondParam.getType() == TokenType::Wildcard) {
        allModifiesStmts = modifiesSReader
                ->getAllStmtsThatModifyAnyVariable();
    } else {

        allModifiesStmts = modifiesSReader
                ->getAllStmtsThatModifyVariable(extractQuotedExpression(secondParam));
    }

    // check what type of statement is the firstParam
    string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    // filter the statements that modifies the variable based on the stmt type
    std::unordered_set<int> allFilteredModifiesStmts;
    allFilteredModifiesStmts = getFilteredStmtsNumByType(allModifiesStmts, statementType, pkbReaderManager);


    // get all filtered statements that modifies the variable
    resultTable->insertColumn(firstParam.getValue());
    for (int stmt: allFilteredModifiesStmts) {
        std::unordered_map<std::string,std::string> newRow;
        newRow[firstParam.getValue()] = to_string(stmt);
        resultTable->insertNewRow(newRow);
    }
}


void ModifiesStrategy::processSecondParam(const Token &firstParam, const Token &secondParam,
                                          const ParsingResult &parsingResult,
                                          std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) {
    // get all variables that are modified by a statement
    std::unordered_set<std::string> allModifiedVars;
    if (firstParam.getType() == TokenType::Wildcard) {
        allModifiedVars = modifiesSReader
                ->getAllVariablesModifiedByAnyStmt();
    } else {
        allModifiedVars = modifiesSReader
                ->getAllVariablesModifiedByStmt(stoi(firstParam.getValue()));
    }
    // add to result
    resultTable->insertColumn(secondParam.getValue());
    for (const std::string &var: allModifiedVars) {
        std::unordered_map<std::string, std::string> newRow;
        newRow[secondParam.getValue()] = var;
        resultTable->insertNewRow(newRow);
    }
}

void ModifiesStrategy::processBothConstants(const Token &firstParam, const Token &secondParam,
                                            const ParsingResult &parsingResult,
                                            std::shared_ptr<ResultTable> resultTable) {
    // check if the statement modifies the variable
    string extractedVar = extractQuotedExpression(secondParam);
    bool modifies = modifiesSReader
            ->doesStmtModifyVariable(stoi(firstParam.getValue()), extractedVar);
    if (modifies) {
        resultTable->setAsTruthTable();
    }
}

void ModifiesStrategy::processWildCards(const Token& firstParam, const Token& secondParam, std::shared_ptr<ResultTable> resultTable) {
    // check if there is any statement that modifies a variable
    if (firstParam.getType() == TokenType::Wildcard && secondParam.getType() == TokenType::Wildcard) {
        std::unordered_set<int> allModifiesStmts = modifiesSReader
                ->getAllStmtsThatModifyAnyVariable();
        if (!allModifiesStmts.empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (firstParam.getType() == TokenType::Wildcard) {
        std::unordered_set<int> allModifiesStmts = modifiesSReader
                ->getAllStmtsThatModifyVariable(
                extractQuotedExpression(secondParam));
        if (!allModifiesStmts.empty()) {
            resultTable->setAsTruthTable();
        }
    } else if (secondParam.getType() == TokenType::Wildcard) {
        std::unordered_set<std::string> allModifiedVars = modifiesSReader
                ->getAllVariablesModifiedByStmt(
                stoi(firstParam.getValue()));
        if (!allModifiedVars.empty()) {
            resultTable->setAsTruthTable();
        }
    }
}