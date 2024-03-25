#include "PatternStrategy.h"


std::shared_ptr<StatementReader> PatternStrategy::getStatementReader() {
    return statementReader;
}

void PatternStrategy::insertRowsWithTwoCols(Token firstParam, Token relationship, ParsingResult parsingResult,
                                            shared_ptr<IControlPatternReader> reader, shared_ptr<ResultTable> resultTable) {
    std::unordered_set<int> allStmts;


    allStmts = reader->getAllStatementNumbers();
    for (auto stmt : allStmts) {
        std::unordered_set<std::string> foundVariables = reader->getControlPatternsWithStatementNumber(stmt);
        for (auto var : foundVariables) {
            pair<string, string> col1 = make_pair(firstParam.getValue(), var);
            pair<string, string> col2 = make_pair(relationship.getValue(), to_string(stmt));
            insertRowToTable(col1, col2, resultTable);
        }
    }
}

