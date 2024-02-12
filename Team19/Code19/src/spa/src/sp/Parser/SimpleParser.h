#pragma once

#include <vector>
#include "sp/Tokenizer.h"
#include "sp/LexicalToken.h"
#include "CallStmt.h"
#include "ReadStmt.h"
#include "PrintStmt.h"

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/cJLjmmneCEs4z6ms7ZkBSxJB?model=gpt-4&mode=chat
class SimpleParser {
public:
    SimpleParser(std::string);
    void parseProgram();

// private:
    std::vector<LexicalToken> tokenStream;
    int tokenIndex;
    bool hasTokensLeft() const;
    LexicalToken peekToken() const;
    LexicalToken SimpleParser::getToken();
    void parseProcedure();
    void parseStmtLst();
    void parseStmt();
    ReadStmt parseRead();
    PrintStmt parsePrint();
    CallStmt parseCall();
    void parseWhile();
    void parseIf();
    void parseAssign();
    void parseCondExpr();
    void parseRelExpr();
    void parseRelFactor();
    void parseExpr();
    void parseTerm();
    void parseFactor();
    void parseVarName();
    void parseProcName();
    void parseConstValue();
};
// ai-gen end