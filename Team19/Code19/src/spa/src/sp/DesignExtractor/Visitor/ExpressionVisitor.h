#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"

#include <iostream>
#include <stdexcept>

class ExpressionVisitor : public IVisitor {
public:
	ExpressionVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};