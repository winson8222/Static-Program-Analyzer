#pragma once

#include "sp/DesignExtractor/Extractor/IfElseThenExtractor.h"
#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/RelExpressionVisitor.h"
#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"
#include <stdexcept>

class IfElseThenVisitor : public StatementVisitor {
public:
	IfElseThenVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);
	void visit() override;
};