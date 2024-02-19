#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"

// ai-gen starts
// prompt: https://platform.openai.com/playground/p/WEPuYktjSFWSXYtIjbHMb5KZ?model=gpt-4&mode=chat

class CallVisitor : public IVisitor {
public:
	CallVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
			: IVisitor(root, pkbWriterManager) {}

	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};

// ai-gen ends