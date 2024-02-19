#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"

// ai-gen start (gpt, 2, e)
// prompt: https://platform.openai.com/playground/p/WEPuYktjSFWSXYtIjbHMb5KZ?model=gpt-4&mode=chat


class AssignVisitor : public IVisitor {
public:
	AssignVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
			: IVisitor(root, pkbWriterManager) {}

	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};

// ai-gen end