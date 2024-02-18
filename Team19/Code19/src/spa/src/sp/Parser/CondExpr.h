#pragma once

#include "Grammar.h"
#include <vector>

class CondExpr : public Grammar {
public:
	CondExpr(int start, int end);
	std::shared_ptr<ASTNode> buildTree() override;
	int getStartLine() const override;
	int getEndLine() const override;

private:
	std::pair<int, int> lines;
};
