#pragma once

#include "Grammar.h"
#include <vector>

class StmtList : public Grammar {
public:
	StmtList(int start, int end, std::vector<std::shared_ptr<ASTNode>> statements);
	std::shared_ptr<ASTNode> buildTree() override;
	int getStartLine() const override;
	int getEndLine() const override;

private:
	std::vector<std::shared_ptr<ASTNode>> statements;
	std::pair<int, int> lines;
};
