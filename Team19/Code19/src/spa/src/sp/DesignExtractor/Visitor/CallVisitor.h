#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/CallExtractor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"

// ai-gen starts
// prompt: https://platform.openai.com/playground/p/WEPuYktjSFWSXYtIjbHMb5KZ?model=gpt-4&mode=chat

class CallVisitor : public StatementVisitor {
public:
	CallVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
			: StatementVisitor(root, pkbWriterManager) {}

	void visit() override;
};

// ai-gen ends