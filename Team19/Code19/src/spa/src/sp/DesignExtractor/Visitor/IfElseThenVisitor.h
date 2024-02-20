#pragma once

#include "sp/DesignExtractor/Extractor/IfElseThenExtractor.h"
#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"
#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"
#include "sp/DesignExtractor/Extractor/ParentExtractor.h"
#include <stdexcept>

class IfElseThenVisitor : public StatementVisitor {
public:
	IfElseThenVisitor(std::shared_ptr<ASTNode> root, 
		listnode context,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);
	void visit() override;
	void addContext(std::shared_ptr<ASTNode> context) override;
};