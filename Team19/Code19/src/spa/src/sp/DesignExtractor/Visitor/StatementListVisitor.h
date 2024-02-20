#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/VisitoryFactory.h"
#include "sp/Utility.h"
#include <stdexcept>
#include <iostream>

class StatementListVisitor : public IVisitor {
public:
	StatementListVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {}

	void visit() override;
};