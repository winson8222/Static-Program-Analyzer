#include "ModifiesStrategy.h"

std::shared_ptr<ResultTable> ModifiesStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult)
{
    auto resultTable = make_shared<ResultTable>();
    this->pkbReaderManager = pkbReaderManager;
    this->ModifiesSReader = pkbReaderManager.getModifiesSReader();


    const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
    const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();

    if (suchThatFirstParam.getType() == TokenType::IDENT && suchThatSecondParam.getType() == TokenType::IDENT) {
        processBothSynonyms(suchThatFirstParam, suchThatSecondParam, resultTable);
    } else if (suchThatFirstParam.getType() == TokenType::IDENT) {
        processFirstParam(suchThatFirstParam, suchThatSecondParam, resultTable);
    } else if (suchThatSecondParam.getType() == TokenType::IDENT) {
        processFirstParam(suchThatFirstParam, suchThatSecondParam, resultTable);
    } else if (isBothParamsWildcard(suchThatFirstParam, suchThatSecondParam)) {
        processBothWildCards(resultTable);
    } else {
        throw "Invalid Query!";
    }
    return resultTable;
}

void ModifiesStrategy::processBothSynonyms(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
                                           ,std::shared_ptr<ResultTable> resultTable) {
    // get all statements that modifies a variable
    std::unordered_set<int> allModifiesStmts = ModifiesSReader->getAllStmtsThatModifyAnyVariable();
    // check what type of statement is the firstParam
    string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    // filter the statements that modifies the variable based on the stmt type
    std::unordered_set<int> allFilteredModifiesStmts;
    if (statementType == "stmt") {
        allFilteredModifiesStmts = allModifiesStmts;
    } else if (statementType == "read") {
        std::shared_ptr<ReadReader> readReader = pkbReaderManager.getReadReader();
        std::unordered_set<int> allReadStmts = readReader->getAllReads();
        allFilteredModifiesStmts = combineFoundStatements(allModifiesStmts, allReadStmts);
    } else if (statementType == "assign") {
        std::shared_ptr<AssignReader> assignReader = pkbReaderManager.getAssignReader();
        std::unordered_set<int> allAssignStmts = assignReader->getAllAssigns();
        allFilteredModifiesStmts = combineFoundStatements(allModifiesStmts, allAssignStmts);
    } else if (statementType == "while") {
        std::shared_ptr<WhileReader> whileReader = pkbReaderManager.getWhileReader();
        std::unordered_set<int> allWhileStmts = whileReader->getAllWhiles();
        allFilteredModifiesStmts = combineFoundStatements(allModifiesStmts, allWhileStmts);
    } else if (statementType == "if") {
        std::shared_ptr<IfReader> ifReader = pkbReaderManager.getIfReader();
        std::unordered_set<int> allIfStmts = ifReader->getAllIfs();
        allFilteredModifiesStmts = combineFoundStatements(allModifiesStmts, allIfStmts);
    } else if (statementType == "print") {
        std::shared_ptr<PrintReader> printReader = pkbReaderManager.getPrintReader();
        std::unordered_set<int> allPrintStmts = printReader->getAllPrints();
        allFilteredModifiesStmts = combineFoundStatements(allModifiesStmts, allPrintStmts);
    } else {
        throw "Invalid Query!";
    }

    // get all variables that are modified by a statement
    resultTable->addColumnsSet({firstParam.getValue(), secondParam.getValue()});
    for (int stmt: allFilteredModifiesStmts) {
        std::unordered_set<std::string> allModifiedVars = ModifiesSReader->getAllVariablesModifiedByStmt(stmt);
        for (const std::string &var: allModifiedVars) {
            std::unordered_map<std::string, std::string> row;
            row[firstParam.getValue()] = std::to_string(stmt);
            row[secondParam.getValue()] = var;
            resultTable->insertNewRow(row);
        }
    }
}

void ModifiesStrategy::processFirstParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
                                         ,std::shared_ptr<ResultTable> resultTable) {
    // get all statements that modifies a variable
    std::unordered_set<int> allModifiesStmts = ModifiesSReader->getAllStmtsThatModifyVariable(secondParam.getValue());
    // check what type of statement is the firstParam
    string statementType = parsingResult.getDeclaredSynonym(firstParam.getValue());
    // filter the statements that modifies the variable based on the stmt type
    std::unordered_set<int> allFilteredModifiesStmts;
    if (statementType == "stmt") {
        allFilteredModifiesStmts = allModifiesStmts;
    } else if (statementType == "read") {
        std::shared_ptr<ReadReader> readReader = pkbReaderManager.getReadReader();
        std::unordered_set<int> allReadStmts = readReader->getAllReads();
        allFilteredModifiesStmts = combineFoundStatements(allModifiesStmts, allReadStmts);
    } else if (statementType == "assign") {
        std::shared_ptr<AssignReader> assignReader = pkbReaderManager.getAssignReader();
        std::unordered_set<int> allAssignStmts = assignReader->getAllAssigns();
        allFilteredModifiesStmts = combineFoundStatements(allModifiesStmts, allAssignStmts);
    } else if (statementType == "while") {
        std::shared_ptr<WhileReader> whileReader = pkbReaderManager.getWhileReader();
        std::unordered_set<int> allWhileStmts = whileReader->getAllWhiles();
        allFilteredModifiesStmts = combineFoundStatements(allModifiesStmts, allWhileStmts);
    } else if (statementType == "if") {
        std::shared_ptr<IfReader> ifReader = pkbReaderManager.getIfReader();
        std::unordered_set<int> allIfStmts = ifReader->getAllIfs();
        allFilteredModifiesStmts = combineFoundStatements(allModifiesStmts, allIfStmts);
    } else if (statementType == "print") {
        std::shared_ptr<PrintReader> printReader = pkbReaderManager.getPrintReader();
        std::unordered_set<int> allPrintStmts = printReader->getAllPrints();
        allFilteredModifiesStmts = combineFoundStatements(allModifiesStmts, allPrintStmts);
    } else {
        throw "Invalid Query!";
    }


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
                                          std::shared_ptr<ResultTable> resultTable) {
    // get all variables that are modified by a statement
    std::unordered_set<std::string> allModifiedVars = ModifiesSReader->getAllVariablesModifiedByStmt(
            stoi(firstParam.getValue()));
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
    bool modifies = ModifiesSReader->doesStmtModifyVariable(stoi(firstParam.getValue()), secondParam.getValue());
    if (modifies) {
        resultTable->setAsTruthTable();
    }
}

void ModifiesStrategy::processBothWildCards(std::shared_ptr<ResultTable> resultTable) {
    // check if there is any statement that modifies a variable
    std::unordered_set<int> allModifiesStmts = ModifiesSReader->getAllStmtsThatModifyAnyVariable();
    if (!allModifiesStmts.empty()) {
        resultTable->setAsTruthTable();
    }
}