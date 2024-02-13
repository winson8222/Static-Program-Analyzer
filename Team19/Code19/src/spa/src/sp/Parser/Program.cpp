#include "Program.h"

// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/3mLKCsoXcgjIM0eMlvP3rIgb?model=gpt-4&mode=chat
Program::Program(int end, std::vector<std::shared_ptr<ASTNode>> procedures) {
	this->lines = std::make_pair(1, end);
	this->procedures = procedures;
}

int Program::getStartLine() const {
	return this->lines.first;
}

int Program::getEndLine() const {
	return this->lines.second;
}

std::shared_ptr<ASTNode> Program::buildTree() {
	std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
		ASTNodeType::PROGRAMS, this->lines.first, Utility::getASTNodeType(ASTNodeType::PROGRAMS)
	);

	for (auto child : this->procedures) {
		tree.get()->addChild(child);
	}

	return tree;
}
// ai-gen end
