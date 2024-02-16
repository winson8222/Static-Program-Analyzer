#pragma once

#include "Stmt.h"
#include "sp/LexicalToken.h"
#include <string>

class AssignStmt : public Stmt {
public:
	AssignStmt(const LexicalToken& variable, const LexicalToken& expr, int start, int end);

	std::shared_ptr<ASTNode> buildTree() override;
	int getStartLine() const override;
	int getEndLine() const override;

private:
	LexicalToken variable;
	LexicalToken expr;
	std::pair<int, int> lines;
};
