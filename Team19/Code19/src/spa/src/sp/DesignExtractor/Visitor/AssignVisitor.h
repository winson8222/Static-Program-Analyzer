#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/AssignExtractor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include "sp/DesignExtractor/Extractor/ParentExtractor.h"
#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"
#include <stdexcept>

// ai-gen start (gpt, 2, e)
// prompt: https://platform.openai.com/playground/p/WEPuYktjSFWSXYtIjbHMb5KZ?model=gpt-4&mode=chat


class AssignVisitor : public StatementVisitor {
public:
	AssignVisitor(std::shared_ptr<ASTNode> root, listnode context, std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;
	void addContext(std::shared_ptr<ASTNode> context) override;
};

// ai-gen end