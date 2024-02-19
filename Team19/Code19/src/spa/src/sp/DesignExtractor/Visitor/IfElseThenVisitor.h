#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"

class IfElseThenVisitor : public IVisitor {
public:
	IfElseThenVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {}
	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};