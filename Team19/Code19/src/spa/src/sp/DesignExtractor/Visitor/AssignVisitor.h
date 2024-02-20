#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/AssignExtractor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include <stdexcept>

// ai-gen start (gpt, 2, e)
// prompt: https://platform.openai.com/playground/p/WEPuYktjSFWSXYtIjbHMb5KZ?model=gpt-4&mode=chat


class AssignVisitor : public StatementVisitor {
public:
	AssignVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;
};

// ai-gen end