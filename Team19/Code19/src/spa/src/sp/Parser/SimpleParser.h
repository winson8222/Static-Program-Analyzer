#pragma once

#include <vector>
#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SPTokenizer/LexicalToken.h"
#include "sp/SPTokenizer/FileProcessor.h"
#include "CallStmt.h"
#include "ReadStmt.h"
#include "PrintStmt.h"
#include "AssignStmt.h"
#include "StmtList.h"
#include "Procedure.h"
#include "Program.h"

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/cJLjmmneCEs4z6ms7ZkBSxJB?model=gpt-4&mode=chat
class SimpleParser {
public:
	SimpleParser(std::string filename);
	std::shared_ptr<ASTNode> parseProgram();

private:
	std::vector<LexicalToken> tokenStream;
	int tokenIndex;
	void assertToken(LexicalToken token, LexicalTokenType type) const;
	bool hasTokensLeft() const;
	LexicalToken peekNextToken();
	LexicalToken getNextToken();
	LexicalToken peekNextNextToken();
	std::shared_ptr<ASTNode> parseProcedure();
	std::shared_ptr<ASTNode> parseStmtLst();
	std::shared_ptr<ASTNode> parseStmt();
	std::shared_ptr<ASTNode> parseRead();
	std::shared_ptr<ASTNode> parsePrint();
	std::shared_ptr<ASTNode> parseCall();
	void parseWhile();
	void parseIf();
	std::shared_ptr<ASTNode> parseAssign();
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