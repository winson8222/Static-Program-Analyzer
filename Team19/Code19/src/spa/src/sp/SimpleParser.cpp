#include "SimpleParser.h"
#include <stdexcept>

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/cJLjmmneCEs4z6ms7ZkBSxJB?model=gpt-4&mode=chat
SimpleParser::SimpleParser(std::string filename) {
    Tokenizer t;
    tokenStream = t.tokenize(t.readFileToString(filename));
}

void SimpleParser::parseProg() {
    while (!tokenStream.empty()) {
        parseProc();
    }
}

void SimpleParser::parseProc() {
    // Add parsing logic for procedure
}

void SimpleParser::parseStmtLst() {
    // Add parsing logic for statement list
}

void SimpleParser::parseStmt() {
    // Add parsing logic for statement
}

void SimpleParser::parseRead() {
    // Add parsing logic for read
}

void SimpleParser::parsePrint() {
    // Add parsing logic for print
}

void SimpleParser::parseCall() {
    // Add parsing logic for call
}

void SimpleParser::parseWhile() {
    // Add parsing logic for while
}

void SimpleParser::parseIf() {
    // Add parsing logic for if statement
}

void SimpleParser::parseAssign() {
    // Add parsing logic for assignment
}

void SimpleParser::parseCondExpr() {
    // Add parsing logic for condition expression
}

void SimpleParser::parseRelExpr() {
    // Add parsing logic for relational expression
}

void SimpleParser::parseRelFactor() {
    // Add parsing logic for relational factor (variable name or constant value or expression)
}

void SimpleParser::parseExpr() {
    // Add parsing logic for expression (term or expression "+" term or expression "-" term)
}

void SimpleParser::parseTerm() {
    // Add parsing logic for term (factor or term "*" factor or term "/" factor or term "%" factor)
}

void SimpleParser::parseFactor() {
    // Add parsing logic for factor (variable name or constant value or "(" expr ")")
}

void SimpleParser::parseVarName() {
    // Add parsing logic for variable name
}

void SimpleParser::parseProcName() {
    // Add parsing logic for procedure name
}

void SimpleParser::parseConstValue() {
    // Add parsing logic for constant value parsing
}
// ai-gen end