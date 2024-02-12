#include "SimpleParser.h"
#include <stdexcept>
#include <iostream>

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/cJLjmmneCEs4z6ms7ZkBSxJB?model=gpt-4&mode=chat


SimpleParser::SimpleParser(std::string filename) {
    this->tokenStream = Tokenizer::tokenize(Tokenizer::readFileToString(filename));
}

void SimpleParser::parseProgram() {
    while (!tokenStream.empty()) {
        parseProcedure();
    }
}

bool SimpleParser::hasTokensLeft(int tokenPos) const {
    return tokenPos < this -> tokenStream.size();
}

// Implementation of getToken function
LexicalToken SimpleParser::getToken(int tokenPos) const {
    if (this->hasTokensLeft(tokenPos)) {
        return this->tokenStream[tokenPos];
    }
    else {
        return LexicalToken(LexicalTokenType::NULL_TOKEN);
    }
}

void SimpleParser::parseProcedure() {
    // Add parsing logic for procedure
}

void SimpleParser::parseStmtLst() {
    // Add parsing logic for statement list
    // Parse every statement until we see a closing bracket.
}

void SimpleParser::parseStmt(int tokenPos) {
    // Add parsing logic for statement
    // If next token is '=', we are assigning. Call assign.
    // Then, Check keywords read/print/call.
    // Then, check keywords while/if.
    // If dont have keyword, this is an invalid statement.
    if (!this->hasTokensLeft(tokenPos)) {
        return;
    }

    LexicalToken firstToken = this->tokenStream[tokenPos];
    if (firstToken.getTokenType() == LexicalTokenType::KEYWORD_CALL
        ) {
        this->parseCall(tokenPos);
    }
    if (

        firstToken.getTokenType() == LexicalTokenType::KEYWORD_PRINT
        ) {
        this->parsePrint(tokenPos);
    }

    if (

        firstToken.getTokenType() == LexicalTokenType::KEYWORD_READ
        ) {
        this->parseRead(tokenPos);
    }

}

ReadStmt SimpleParser::parseRead(int tokenPos) {
    // Problem: Need to potential pass tokenPos as a pointer.
    LexicalToken keyword = this->getToken(tokenPos);
    tokenPos++;

    if (keyword.getTokenType() != LexicalTokenType::KEYWORD_READ) {
        throw std::runtime_error("Error: Invalid SIMPLE syntax.");
    }

    LexicalToken variable = this->getToken(tokenPos);
    tokenPos++;

    if (variable.getTokenType() != LexicalTokenType::NAME) {
        throw std::runtime_error("Error: Invalid SIMPLE syntax.");
    }

    LexicalToken semicolon = this->getToken(tokenPos);
    tokenPos++;

    if (semicolon.getTokenType() != LexicalTokenType::SYMBOL_SEMICOLON) {
        throw std::runtime_error("Error: Invalid SIMPLE syntax.");
    }

    return ReadStmt(variable, keyword.getLine(), semicolon.getLine());

    // Add the readStmt to the Tree.
}

void SimpleParser::parsePrint(int tokenPos) {
    // Add parsing logic for print
}

// To change to void later when building trees.
CallStmt SimpleParser::parseCall(int tokenPos) {
    // Problem: Need to potential pass tokenPos as a pointer.
    LexicalToken keyword = this->getToken(tokenPos);
    tokenPos++;

    if (keyword.getTokenType() != LexicalTokenType::KEYWORD_CALL) {
        throw std::runtime_error("Error: Invalid SIMPLE syntax.");
    }

    LexicalToken variable = this->getToken(tokenPos);
    tokenPos++;

    if (variable.getTokenType() != LexicalTokenType::NAME) {
        throw std::runtime_error("Error: Invalid SIMPLE syntax.");
    }

    LexicalToken semicolon = this->getToken(tokenPos);
    tokenPos++;

    if (semicolon.getTokenType() != LexicalTokenType::SYMBOL_SEMICOLON) {
        throw std::runtime_error("Error: Invalid SIMPLE syntax.");
    }

    return CallStmt(variable, keyword.getLine(), semicolon.getLine());

    // Add the callStmt to the Tree.
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