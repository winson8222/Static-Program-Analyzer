#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"

class IfElseThenVisitor : public IVisitor {
public:
	IfElseThenVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
			: IVisitor(root, pkbWriterManager) {}
	virtual void visit(std::shared_ptr<ASTNode> node) = 0;
};