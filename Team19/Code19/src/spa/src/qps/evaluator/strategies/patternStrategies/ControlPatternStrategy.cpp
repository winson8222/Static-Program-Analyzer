#include "IfPatternStrategy.h"
#include <memory>


std::shared_ptr<ResultTable> ControlPatternStrategy::getEvaluatedResultTable(PKBReaderManager &pkbReaderManager,
                                                                             const ParsingResult &parsingResult,
                                                                             std::shared_ptr<ResultTable> resultTable) {
    if (firstParam.getType() == TokenType::IDENT) {
        processSynonyms(parsingResult, resultTable);
    } else if (firstParam.getType() == TokenType::QuoutIDENT) {
        processQuotedIdent(parsingResult, resultTable);
    } else if (firstParam.getType() == TokenType::Wildcard) {
        processWildcard(parsingResult, resultTable);
    } else {
        throw "Invalid firstParam type";
    }

    return resultTable;
}