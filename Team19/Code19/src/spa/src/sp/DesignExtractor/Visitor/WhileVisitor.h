#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"

class WhileVisitor : public IVisitor {
public:
	WhileVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {}

	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};