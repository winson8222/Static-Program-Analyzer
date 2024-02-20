#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/CallExtractor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include "sp/DesignExtractor/Extractor/ParentExtractor.h"

// ai-gen starts
// prompt: https://platform.openai.com/playground/p/WEPuYktjSFWSXYtIjbHMb5KZ?model=gpt-4&mode=chat

class CallVisitor : public StatementVisitor {
public:
	CallVisitor(std::shared_ptr<ASTNode> root, 
		listnode context,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
			: StatementVisitor(root, context, pkbWriterManager) {
		// TODO
		this->contexts = listnode(context.begin(), context.end());
	}

	void visit() override;
	void addContext(std::shared_ptr<ASTNode> context);
};

// ai-gen ends