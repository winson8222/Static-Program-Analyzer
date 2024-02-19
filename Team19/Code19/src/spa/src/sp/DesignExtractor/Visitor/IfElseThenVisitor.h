#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"
#include "sp/DesignExtractor/Visitor/StatementListVisitor.h"
#include <stdexcept>

class IfElseThenVisitor : public IVisitor {
public:
	IfElseThenVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager);
	void visit(std::shared_ptr<ASTNode> node) override;
	void visit() override;
};