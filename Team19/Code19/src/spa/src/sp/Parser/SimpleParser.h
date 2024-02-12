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
    bool hasTokensLeft(int tokenPos) const;
    LexicalToken peekToken(int tokenPos) const;
    void parseProcedure();
    void parseStmtLst();
    void parseStmt(int tokenPos);
    ReadStmt parseRead(int tokenPos);
    PrintStmt parsePrint(int tokenPos);
    CallStmt parseCall(int tokenPos);
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