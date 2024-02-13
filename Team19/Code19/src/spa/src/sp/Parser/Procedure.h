#pragma once

#include "Grammar.h"
#include "StmtList.h"
#include <vector>
#include <string>

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
class Procedure : public Grammar {
public:
	Procedure(int start, int end, std::shared_ptr<ASTNode> statementListTree);
	int getStartLine() const override;
	int getEndLine() const override;
	std::shared_ptr<ASTNode> buildTree() override;

private:
	std::shared_ptr<ASTNode> statementListTree;
	std::pair<int, int> lines;
};
// ai-gen end
