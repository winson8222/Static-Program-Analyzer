#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"

// ai-gen start (gpt, 2, e)
// prompt: https://platform.openai.com/playground/p/WEPuYktjSFWSXYtIjbHMb5KZ?model=gpt-4&mode=chat


class AssignVisitor : public StatementVisitor {
public:
	AssignVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
			: StatementVisitor(root, pkbWriterManager) {}

	void visit() override;
};

// ai-gen end