#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/CallExtractor.h"
#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"
#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"
#include "sp/DesignExtractor/Extractor/ParentExtractor.h"

// ai-gen starts
// prompt: https://platform.openai.com/playground/p/WEPuYktjSFWSXYtIjbHMb5KZ?model=gpt-4&mode=chat

class CallVisitor : public StatementVisitor {
public:
	CallVisitor(std::shared_ptr<ASTNode> root,
		listnode context,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;
	std::vector<std::shared_ptr<ASTNode>> getProcedureContexts();
};

// ai-gen ends