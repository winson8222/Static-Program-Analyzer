#pragma once

#include "Procedure.h"
#include "Grammar.h"
#include <vector>

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
class Program : public Grammar {
public:
	Program(int end, std::vector<std::shared_ptr<ASTNode>> procedures);

	int getStartLine() const override;
	int getEndLine() const override;
	std::shared_ptr<ASTNode> buildTree() override;

private:
	std::vector<std::shared_ptr<ASTNode>> procedures;
	std::pair<int, int> lines;
};
// ai-gen end