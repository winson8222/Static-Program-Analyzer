#include "PatternStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>




std::shared_ptr<StatementReader> PatternStrategy::getStatementReader() {
    return statementReader;
}

void PatternStrategy::insertRowsWithTwoCols(Token firstParam, Token relationship, ParsingResult parsingResult,
                                            std::shared_ptr<IControlPatternReader> reader, std::shared_ptr<ResultTable> resultTable) {
    std::unordered_set<int> allStmts;


    allStmts = reader->getAllStatementNumbers();
    for (auto stmt : allStmts) {
        std::unordered_set<std::string> foundVariables = reader->getControlPatternsWithStatementNumber(stmt);
        for (auto var : foundVariables) {
            std::pair<std::string, std::string> col1 = make_pair(firstParam.getValue(), var);
            std::pair<std::string, std::string> col2 = make_pair(relationship.getValue(), std::to_string(stmt));
            insertRowToTable(col1, col2, resultTable);
        }
    }
}

void PatternStrategy::setRelationship(Token relationShip) {
    this->relationship = relationShip;
}

