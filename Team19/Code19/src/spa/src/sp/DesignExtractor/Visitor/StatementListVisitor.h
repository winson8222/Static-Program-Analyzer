#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"

class StatementListVisitor : public IVisitor {
public:
	StatementListVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {}

	void visit(StatementListNode& node) override;
};