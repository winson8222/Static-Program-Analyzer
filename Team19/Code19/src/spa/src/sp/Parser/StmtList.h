#pragma once

#include "Grammar.h"
#include "CallStmt.h"
#include <vector>

class StmtList : public Grammar {
public:
	StmtList(int start, int end);
	void addStmt(std::shared_ptr<ASTNode> statementNode);
	std::shared_ptr<ASTNode> buildTree() override;
	int getStartLine() const override;
	int getEndLine() const override;

private:
	std::vector<std::shared_ptr<ASTNode>> statements;
	std::pair<int, int> lines;
};
