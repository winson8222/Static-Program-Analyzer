#pragma once

#include <vector>
#include "sp/Tokenizer.h"
#include "sp/LexicalToken.h"
#include "CallStmt.h"

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/cJLjmmneCEs4z6ms7ZkBSxJB?model=gpt-4&mode=chat
class SimpleParser {
public:
    SimpleParser(); // Default constructor
    SimpleParser(std::string filename);
    void parseProgram();

// private:
    std::vector<LexicalToken> tokenStream;
    bool hasTokensLeft(int tokenPos) const;
    LexicalToken getToken(int tokenPos) const;
    void parseProcedure();
    void parseStmtLst();
    void parseStmt(int tokenPos);
    void parseRead();
    void parsePrint();
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