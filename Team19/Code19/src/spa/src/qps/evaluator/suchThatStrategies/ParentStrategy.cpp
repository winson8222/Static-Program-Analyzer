#include "ParentStrategy.h"
#include "qps/parser/Token.h" // Include the Token header

using namespace std;

// The ParentStrategy class evaluates queries to find parents relationships in a program.
// A parents relationship is defined between two statements (stmtRef, stmtRef),
// where a stmtRef can be a wildcard, an integer, or a synonym.

std::shared_ptr<ResultTable> ParentStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) {

    auto resultTable = make_shared<ResultTable>();


    return resultTable;
}



// Additional helper methods for readability
void ParentStrategy::processFirstParam(const Token& firstParam, const Token& secondParam, const string& variant,
                                       std::shared_ptr<ResultTable> resultTable) {
    return;
}



void ParentStrategy::processIntegerParams(const Token& firstParam, const Token& secondParam,
                                          std::shared_ptr<ResultTable> resultTable) {
   return;
}

void ParentStrategy::processSynonyms(const Token& firstParam, const Token& secondParam,
                                     const string& variant, std::shared_ptr<ResultTable> resultTable) {
    // Implementation for processing when both parameters are synonyms
    return;
}
