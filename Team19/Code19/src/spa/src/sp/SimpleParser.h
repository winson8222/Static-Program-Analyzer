#pragma once

#include"Tokenizer.h"
#include"LexicalToken.h"

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/cJLjmmneCEs4z6ms7ZkBSxJB?model=gpt-4&mode=chat
class SimpleParser {
public:
    SimpleParser(std::string);
    void parseProg();
private:
    std::vector<LexicalToken> tokenStream;
    void parseProc();
    void parseStmtLst();
    void parseStmt();
    void parseRead();
    void parsePrint();
    void parseCall();
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