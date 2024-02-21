#pragma once

#include "sp/DesignExtractor/Visitor/IVisitor.h"
#include "sp/DesignExtractor/Visitor/VisitoryFactory.h"
#include "sp/DesignExtractor/Extractor/FollowsExtractor.h"
#include "sp/Utility.h"
#include <stdexcept>
#include <iostream>
#include <vector>

class StatementListVisitor : public IVisitor {
public:
	StatementListVisitor(std::shared_ptr<ASTNode> root, 
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IVisitor(root, pkbWriterManager) {}

	void visit() override;
	void setContext(std::vector<std::shared_ptr<ASTNode>> contexts, std::shared_ptr<ASTNode> parent);
	std::vector<std::shared_ptr<ASTNode>> contexts;
};