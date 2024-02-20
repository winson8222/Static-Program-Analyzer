#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include "sp/DesignExtractor/Extractor/ConstantExtractor.h"
#include "sp/Utility.h"

#include <iostream>
#include <stdexcept>

class RelExpressionVisitor : public IVisitor {
public:
	RelExpressionVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit() override;

private:
	void depthFirstSearch(std::shared_ptr<ASTNode> node);
};